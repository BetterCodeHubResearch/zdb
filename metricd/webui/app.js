/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2016 Laura Schlimmer
 *   Copyright (c) 2016 Paul Asmuth
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */

this["FnordMetric"] = (function() {
  var app = this;
  var router;
  var widgets = {};
  var current_path = win.location.pathname + win.location.search;

  var init = function() {
    console.log(">> FnordMetric v0.10");

    document.querySelector(".headbar").style.display = "block";
    showLoader();
    setRoute(navigator.getPath());

    /* handle history entry change */
    setTimeout(function() {
      win.addEventListener('popstate', function(e) {
        e.preventDefault();
        if (e.state && e.state.path) {
          applyNavgiationChange(e.state.path);
        } else {
          applyNavigationChange(win.location.pathname + win.location.search);
        }
      }, false);
    }, 0);
  }

  var navigateTo = function(url) {
    var path zURLUtil.getPathAndQuery(url);
    history.pushState({path: path}, "", path);
    applyNavigationChange(path);
  }

  var applyNavigationChange = function(path) {
    if (path == current_path) {
      return;
    }

    current_path = path;
    setRoute(path);
  };

  var navigateHome = function() {
    navigateTo("/");
  }

  var setRoute = function(path) {
    console.log(">> Navigate to: " + path);

    var params = {};
    params.app = app;
    params.path = path;
    params.api_stubs = api_stubs;
    params.user_info = user_info;

    var m = path.match(/\/a\/([a-z0-9A-Z_-]+)(\/?.*)/);
    if (m) {
      params.project_id = m[1];
      params.vpath = "/a/<namespace>" + m[2];
    } else {
      params.vpath = path;
    }

    var current_view = viewport.getView();
    if (current_view && current_view.changePath) {
      var route = router.findRoute(params.vpath);
      if (current_view.changePath(path, route)) {
        return;
      }
    }

    /* render page */
    loadPage(params);
  }

  var loadPage = function(params) {
    showLoader();
    renderPage(params);
  }

  var renderPage = function(params) {
    var route = params.vpath ? router.findRoute(params.vpath) : null;
    params.route = route;

    var view = route ? FnordMetric.views[route.view] : null;
    if (!view) {
      renderError({type: "404"});
      return;
    }

    //if (route && route.main_menu) {
    //  widgets.main_menu.setActiveItem(route.main_menu_active_item);
    //  widgets.main_menu.showMenu();
    //} else {
    //  widgets.main_menu.hideMenu();
    //}

    hideLoader();
    viewport.setView(view, params);
  }

  var setupAPIStubs = function() {
    api_stubs.user = new UserAPI(app.config.api_hosts.api_user, credentials.api_token);
  }

  var showLoader = function() {
    //FIXME
    //document.getElementById("fm_main_loader").classList.remove("hidden");
  };

  var hideLoader = function() {
    //FIXME
    //document.getElementById("fm_main_loader").classList.add("hidden");
  };

  var renderError = function(cfg) {
    var view = FnordMetric.views["fnordmetric.error"];
    viewport.setView(view, cfg);
  }

  this["init"] = init;
  this.navigateTo = navigateTo;
  this.navigateHome = navigateHome;
  this.showLoader = showLoader;
  this.hideLoader = hideLoader;
  this.renderError = renderError;
  this.views = {};
  this.util = {};
  this.api_stubs = api_stubs;
  return this;
}).apply(this["FnordMetric"] || {});


FnordMetric.util.rewriteLinks = function(elem, project_id) {
  var elems = elem.querySelectorAll("a");
  for (var i = 0; i < elems.length; ++i) {
    elems[i].href = elems[i].href.replace("%project_id%", project_id);
  }
};

FnordMetric.util.rewriteAndHandleLinks = function(elem, project_id) {
  FnordMetric.util.rewriteLinks(elem, project_id);
  zDomUtil.handleLinks(elem, FnordMetric.navigateTo);
}

FnordMetric.util.renderBreadcrumbs = function(elem, crumbs) {
  zDomUtil.clearChildren(elem);

  crumbs.forEach(function(c) {
    var crumb_elem = document.createElement("fm-breadcrumbs-section");
    var crumb_a = document.createElement("a");
    crumb_a.innerHTML = zDomUtil.escapeHTML(c.title);
    if (c.href) {
      crumb_a.setAttribute("href", c.href);
    }

    crumb_elem.appendChild(crumb_a);
    elem.appendChild(crumb_elem);
  });
}
