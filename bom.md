---
layout: default
title: Bill of Materials
permalink: /bom
sequence: 4
---

<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">Overview</h2>

    <div class="content is-large">
      <ul>
        <li><strong>Unique number of items:</strong> <span id="bom-unique"></span></li>
        <li><strong>Total number of items:</strong> <span id="bom-total"></span></li>
        <li><strong>Total cost of items:</strong> <span id="bom-cost"></span></li>
        <li><strong>Total number of vendors:</strong> 5</li>
        <li><strong>Most expensive item:</strong> 3.7 1200mAh LiPo at SGD $14.40</li>
      </ul>
    </div>
  </div>
</section>
<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">Bill of Materials</h2>

    <table class="table is-fullwidth is-hoverable">
      <thead>
        <tr>
          <th>Designator</th>
          <th>Quantity</th>
          <th>Package</th>
          <th>Value</th>
          <th>Manufacturer Part No.</th>
          <th>Manufacturer</th>
          <th>Vendor</th>
          <th>Unit Cost (SGD)</th>
          <th>Total Cost (SGD)</th>
          <th>Minimum Order Quantity</th>
          <th>Description</th>
        </tr>
      </thead>
      <tbody>
        {% assign boms = site.data.bill_of_materials %}
        {% for bom in boms %}
          {% if bom.Designator %}
          <tr class="bom-item">
            <td>{{bom.Designator}}</td>
            <td class="bom-quantity">{{bom.Q}}</td>
            <td>{{bom.Package}}</td>
            <td>{{bom.Value}}</td>
            <td>{{bom.MPN}} <span class="tag">{{bom.Category}}</span></td>
            <td>{{bom.Manufacturer}}</td>
            <td>{{bom.Vendor}}</td>
            <td>{{bom.Unit}}</td>
            <td class="bom-cost">{{bom.Total}}</td>
            <td>{{bom.MOQ}}</td>
            <td>{{bom.Description}}</td>
          </tr>
          {% endif %}
        {% endfor %}
      </tbody>
    </table>

  </div>
</section>
