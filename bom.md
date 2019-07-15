---
layout: default
title: Bill of Materials
permalink: /bom
sequence: 4
---

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
          <th>Unit Cost</th>
          <th>Total Cost</th>
          <th>Minimum Order Quantity</th>
          <th>Description</th>
        </tr>
      </thead>
      <tbody>
        {% assign boms = site.data.bill_of_materials %}
        {% for bom in boms %}
          {% if bom.Designator %}
          <tr>
            <td>{{bom.Designator}}</td>
            <td>{{bom.Q}}</td>
            <td>{{bom.Package}}</td>
            <td>{{bom.Value}}</td>
            <td>{{bom.MPN}}</td>
            <td>{{bom.Manufacturer}}</td>
            <td>{{bom.Vendor}}</td>
            <td>{{bom.Unit}}</td>
            <td>{{bom.Total}}</td>
            <td>{{bom.MOQ}}</td>
            <td>{{bom.Description}}</td>
          </tr>
          {% endif %}
        {% endfor %}
      </tbody>
    </table>

  </div>
</section>
