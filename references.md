---
layout: default
title: References
permalink: /references
sequence: 10
---

{% assign references = site.data.references %}
{% for ref in references %}
<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">{{ ref.topic }}</h2>

    <div class="content is-medium">
      <ol>
        {% for li in ref.list %}
        <li><a href="{{ li.url }}">{{ li.name }}</a></li>
        {% endfor %}
      </ol>
    </div>
  </div>
</section>
{% endfor %}
