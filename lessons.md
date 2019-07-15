---
layout: default
title: Lessons learnt
permalink: /lessons
sequence: 9
---

{% assign lessons = site.data.lessons %}
{% for le in lessons %}
<section class="section is-small">
  <div class="container">

    <h2 class="title is-1">{{ le.title }}</h2>
    {% if le.subtitle %}
    <p class="subtitle">{{le.subtitle}}</p>
    {% endif %}

    <div class="content is-medium">
      <ul>
        {% for li in le.list %}
        <li>{{ li.name }}</li>
        {% endfor %}
      </ul>
    </div>
  </div>
</section>
{% endfor %}
