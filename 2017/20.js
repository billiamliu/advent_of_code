const fname = '20.txt'
const readf = require('fs').readFileSync

function read(name) {
  return readf(name, {encoding: 'utf8'}).trim()
}

function parse(str) {
  return str.split('\n').map((l, i) => [i, ...l.match(/(-?\d+)/g).map(Number)])
}

const abs = point => point.map(Math.abs).reduce((s, n) => s + n, 0)
const getD = p => p.slice(1, 4)
const getV = p => p.slice(4, 7)
const getA = p => p.slice(7, 10)
const manhattan = particle => [particle[0], abs(getD(particle)), abs(getV(particle)), abs(getA(particle))]

function dvaSort(a, b) {
  let ta, tb
  if ((ta = a[3]) !== (tb = b[3])) {}
  else if ((ta = a[2]) !== (tb = b[2])) {}
  else { ta = a[1]; tb = b[1] }
  return ta - tb
}

function small(particles) {
  return particles.map(manhattan).sort(dvaSort)[0][0]
}

function tick(p) {
  p[4] += p[7]
  p[5] += p[8]
  p[6] += p[9]
  p[1] += p[4]
  p[2] += p[5]
  p[3] += p[6]
}

function registerLocation(set, p, i) {
  const d = [p[1], p[2], p[3]].join()
  set[d] = set[d] || []
  set[d].push(i)
}

function collide(particles, collisions) {
  const s = new Set(collisions)
  return particles.filter((p, i) => !s.has(i))
}

function large(particles) {
  const cooldown = 1000
  let temperature = cooldown
  while (temperature--) {
    let set = {}
    let toRemove = []
    particles.forEach((p, i) => registerLocation(set, p, i))
    for (let d in set) {
      if (set[d].length > 1) {
        toRemove = toRemove.concat(set[d])
        temperature = cooldown
      }
    }
    particles = collide(particles, toRemove)
    particles.forEach(tick)
  }
  return particles.length
}

console.log(small(parse(read(fname))))
console.log(large(parse(read(fname))))
