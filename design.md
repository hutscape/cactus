---
layout: default
title: Design
permalink: /design
sequence: 5
---

# Design

## Power tree schematic

> A power tree is a graphical representation of your system’s power management architecture. The power tree illustrates the main supply power flow through a tree of power converters that convert the main supply power to the voltage and current required to drive various loads. - Intel's Creating an FPGA Power Tree

![](power_tree.png)

## State machine

Via [mermaid.js](https://mermaidjs.github.io/)

```
mmdc -i state_machine.md -o state_machine.png
mmdc -i state_machine.md -o state_machine.svg
```

![](state_machine.png)

## References

- [Creating an FPGA Power Tree](https://www.intel.com/content/dam/www/programmable/us/en/pdfs/literature/an/an-721-creating-fpga-power-tree.pdf)
- [System-Level Design Tool Quick Start Guide](https://www.analog.com/media/en/technical-documentation/user-guides/ltpowerplanneriii_qsg.pdf)
