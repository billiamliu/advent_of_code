const fname = '11.txt'
const readf = require('fs').readFileSync

function read(name) {
  return readf(name, {encoding: 'utf8'}).trim()
}

function parse(str) {
  return str.split(',')
}

const directions = {
  n: [-1, 0, 1],
  s: [1, 0, -1],
  ne: [-1, 1, 0],
  sw: [1, -1, 0],
  se: [0, 1, -1],
  nw: [0, -1, 1]
}

function small(input) {
  const dest = input
    .map(step => directions[step])
    .reduce(([xo, yo, zo], [xi, yi, zi]) => [xo + xi, yo + yi, zo + zi], [0, 0, 0])

  return Math.max(...dest.map(coord => Math.abs(coord)))
}

function dist(x, y, z) {
  [x, y, z] = [x, y, z].map(n => Math.abs(n))
  return Math.max(x, y, z)
}

function large(input) {
  return input
    .map(step => directions[step])
    .reduce(([[xo, yo, zo], max], [xi, yi, zi]) => {
      let newPos = [xo + xi, yo + yi, zo + zi]
      let newDist = dist(...newPos)
      return [newPos, newDist > max ? newDist : max]
    }, [[0, 0, 0], 0])
}

console.log(small(parse(read(fname))))
console.log(large(parse(read(fname))))
