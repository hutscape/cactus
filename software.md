---
layout: default
title: Software
permalink: /software
sequence: 3
---

<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">Features</h2>

    <div class="content is-medium">
      <ul>
        <li>Read humidity and temperature values from the sensor <code>Si7021</code></li>
        <li>Read LiPo battery levels</li>
        <li>Display the current humidity value through the on-board LEDs</li>
        <li>Wakeup every <code>6 hours</code> or on button press to read the sensor and send data to the cloud</li>
        <li>Sleep after sending data to IFTTT</li>
        <li>Check for stored WiFi credentials upon waking up and connect back to the store WiFi</li>
        <li>Connect to WiFi with the stored credentials</li>
        <li>Setup an AP mode if WiFi cannot be connected</li>
        <li>Send sensor and battery values to IFTTT if WiFi is connected</li>
        <li>Wait for <code>5 minutes</code> in AP mode is WiFi is not connected</li>
        <li>Sleep after waiting for <code>5 minutes</code> in AP mode</li>
        <li>Charge the LiPo by plugging in the USB cable into the battery shield</li>
      </ul>
    </div>
  </div>
</section>

<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">Firmware</h2>

    <p class="subtitle is-4"><a href="{{site.github.repository_url}}/tree/master/{{page.path | replace:'.md',''}}">Upload the code</a> with <code>make flash</code> command.</p>
    <p>Use firmware version at least <a href="https://github.com/esp8266/Arduino/tree/0da6906499aaa9977f7b456c6ec32c090b117cef">Arduino ESP8266 commit hash <code>0da69064</code></a> and above for mDNS patch.</p>

    {% highlight c %}{%- include_relative firmware/firmware.ino -%}{% endhighlight %}


    <p class="subtitle is-4">Makefile</p>
    {% highlight make %}{%- include_relative firmware/Makefile -%}{% endhighlight %}

    <p class="subtitle is-4">Serial console</p>
    <img src="{{site.url}}/images/software/console.png" alt="Firmware serial console">
  </div>
</section>

<section class="section is-small">
  <div class="container">
    <h2 class="title is-1">Test</h2>

    <p class="subtitle is-4"><a href="{{site.github.repository_url}}/tree/master/test">Upload the code</a> with <code>make flash</code> command.</p>
    {% highlight c %}{%- include_relative test/test.ino -%}{% endhighlight %}

    <p class="subtitle is-4">Makefile</p>
    {% highlight make %}{%- include_relative test/Makefile -%}{% endhighlight %}

    <p class="subtitle is-4">Serial console</p>
    <img src="{{site.url}}/images/software/test-console.png" alt="Firmware serial console">
  </div>
</section>
