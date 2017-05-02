/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2016 Laura Schlimmer, FnordCorp B.V.
 *   Copyright (c) 2016 Paul Asmuth, FnordCorp B.V.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */

FnordMetricTopSeries.Table = function(elem, params) {
  'use strict';

  this.render = function(result) {
    renderHeader();
    renderBody(result);
  }

/********************************** private ***********************************/

  function renderHeader() {
    var head_tr = elem.querySelector("thead");
    var columns = [
      {
        key: "series_id",
        title: "Series ID",
        sortable: true
      },
      {
        key: "summary",
        title: "Value",
        sortable: true,
        attrs: {
          colspan: 2
        }
      },
      {
        key: "menu",
        sortable: false
      }
    ];

    columns.forEach(function(col) {
      head_tr.appendChild(renderHeaderCell(col));
    });

  }

  function renderHeaderCell(col) {
    var th = document.createElement("th");
    th.classList.add(col.key);

    if (col.title) {
      th.innerHTML = DOMUtil.escapeHTML(col.title);
    }

    if (col.sortable) {
      var sort_elem = document.createElement("span");
      sort_elem.classList.add("sort");
      th.appendChild(sort_elem);

      var sort_desc = document.createElement("i");
      sort_desc.classList.add("sort_desc");
      sort_elem.appendChild(sort_desc);

      var sort_asc = document.createElement("i");
      sort_asc.classList.add("sort_asc");
      sort_elem.appendChild(sort_asc);

      switch (col.sorted) {
        case "asc":
          sort_asc.classList.add("active");
          break;
        case "desc":
          sort_desc.classList.add("active");
          break;
      }

      var sort_fn = function(dir) {
        on_sort.forEach(function(f) {
          f(c, dir);
        });
      };

      DOMUtil.onClick(sort_asc, function() {
        sort_fn("asc");
      });

      DOMUtil.onClick(sort_desc, function() {
        sort_fn("desc");
      });
    }

    if (col.attrs) {
      for (var attr in col.attrs) {
        th.setAttribute(attr, col.attrs[attr]) //FIXME escape!
      }
    }

    return th;
  }

  function renderBody(result) {
    var tbody = document.querySelector("tbody");

    result.series.forEach(function(series) {
      tbody.appendChild(renderRow(series));
    });
  }

  function renderRow(series) {
    var tr = document.createElement("tr");
    tr.setAttribute("fm-series", series.series_id); //FIXME escape!

    tr.appendChild(renderIDCell(series.series_id));
    tr.appendChild(renderSparklineCell(series));
    tr.appendChild(renderSummaryCell(series));
    tr.appendChild(renderContextMenuCell());

    return tr;
  }

  function renderIDCell(series_id) {
    var td = document.createElement("td");
    td.classList.add("id");
    td.innerHTML = DOMUtil.escapeHTML(series_id);

    return td;
  }

  function renderSparklineCell(result) {
    var td = document.createElement("td");
    td.classList.add("sparkline");

    var sparkline_elem = document.createElement("div");
    sparkline_elem.classList.add("fm-sparkline");
    td.appendChild(sparkline_elem);

    var sparklines_params = {
      height: 30
    };

    var sparkline_plotter = new FnordMetricTopSeries.SparklinePlotter(
        sparkline_elem,
        sparklines_params);
    sparkline_plotter.render(result);

    return td;
  }

  function renderSummaryCell(series) {
    var td = document.createElement("td");
    td.classList.add("summary");

    var max_summary_elems = 4;
    for (var i = 0; i < series.summaries.length && i < max_summary_elems; i++) {
      var span = document.createElement("span");

      /* render main summary */
      if (i == 0) {
        span.classList.add("main_summary");

      /* render small summary */
      } else {
        span.classList.add("small_summary");
        span.innerHTML = DOMUtil.escapeHTML(series.summaries[i].summary) + "=";
      }

      span.innerHTML += FnordMetricUnits.formatValue(
          series.unit,
          series.summaries[i].value);

      td.appendChild(span);
    }

    return td;
  }

  function renderContextMenuCell() {
    var td = document.createElement("td");
    td.classList.add("caret_down"); //render icon
    return td;
  }
}

