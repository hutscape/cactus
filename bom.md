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
        <li><strong>Total number of vendors:</strong> <span id="bom-vendors"></span></li>
      </ul>
    </div>
  </div>
</section>
<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">Bill of Materials</h2>
    <a href="{{site.url}}/_data/bill_of_materials.csv" class="button is-large is-fullwidth is-info">Download Bill of Materials in CSV</a>

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
            <td>
              {% if bom.Datasheet %}
                {% if bom.MPN %}
                <a href="{{bom.Datasheet}}">{{bom.MPN}}</a><br>
                {% else %}
                <a href="{{bom.Datasheet}}">Datasheet</a><br>
                {% endif %}
              {% else %}
                {% if bom.MPN %}
                {{bom.MPN}}<br>
                {% endif %}
              {% endif %}
              <span class="tag">{{bom.Category}}</span>
            </td>
            <td>{{bom.Manufacturer}}</td>
            <td>
              {% if bom.Link %}
              <a href="{{bom.Link}}"><span class="bom-vendor">{{bom.Vendor}}</span></a>
              {% else %}
              <span class="bom-vendor">{{bom.Vendor}}</span>
              {% endif %}
            </td>
            <td class="bom-cost">${{bom.Unit | round:2}}</td>
            <td>{{bom.Description}}</td>
          </tr>
          {% endif %}
        {% endfor %}
      </tbody>
    </table>
  </div>
</section>
