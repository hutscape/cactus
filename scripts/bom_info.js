const csv = require('csv-parser')
const fs = require('fs')
const results = []

fs.createReadStream(process.cwd() + '/_data/bill_of_materials.csv')
  .pipe(csv())
  .on('data', (data) => results.push(data))
  .on('end', () => {
    var bom = {}
    console.log(results)

    bom['bom-uniq'] = calculateBOMUniq(results)
    bom['bom-total'] = calculateBOMTotal(results)
    bom['bom-cost'] = calculateBOMCost(results)
    bom['vendors'] = calculateBOMVendors(results).vendors
    bom['vendor-names'] = calculateBOMVendors(results).names

    console.log(bom)
    fs.writeFile(process.cwd() + '/_data/bom.json', JSON.stringify(bom,null, 2), 'utf-8', function() {
      console.log('Wrote to file')
    });
  });


function calculateBOMUniq(results) {
  return results.length
}

function calculateBOMTotal(results) {
  var total = 0

  results.forEach(function(r) {
    total += parseInt(r['Q'])
  })

  return total
}

function calculateBOMCost(results) {
  var total = 0

  results.forEach(function(r) {
    if (r['Unit']) {
      total += parseInt(r['Q']) * parseFloat(r['Unit'])
    }
  })

  return total.toFixed(2)
}

function calculateBOMVendors(results) {
  var vendors = []
  var uniqueVendors = []

  results.forEach(function(r) {
    if (r['Vendor']) {
      vendors.push(r['Vendor'])
    }
  })

  uniqueVendors = vendors.filter((v, i, a) => a.indexOf(v) === i)
  return {
    vendors: uniqueVendors.length,
    names: uniqueVendors
  }
}
