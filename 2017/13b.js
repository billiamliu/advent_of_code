const fname = '13.txt'
const readf = require('fs').readFileSync

function read(name) {
  return readf(name, {encoding: 'utf8'}).trim()
}

function parse(str) {
  return str.split('\n').map(l => l.match(/\d+/g).map(n => Number(n)))
}

function hit(delay) {
  return function ([loc, range]) {
    return (delay + loc) % (2 * (range - 1)) === 0
  }
}

function part2(scanners) {
  let delay = -1
  while (scanners.some(hit(++delay)))
    ;
  return delay
}

console.log(part2(parse(read(fname))))
