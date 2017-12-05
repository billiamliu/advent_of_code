const read = require('fs').readFileSync
const fname = '05.txt'

const sm = read(fname, {encoding: 'utf8'})
  .split('\n')
  .map(n => parseInt(n))
sm.pop() // get rid of last blank
const lg = sm.concat([])
const size = sm.length

function small() {
  let i = 0
  let count = 0
  while (i < size) {
    count++
    i = i + sm[i]++
  }

  return count
}

function large() {
  let i, n, count
  i = n = count = 0

  while (i < size) {
    count++
    n = lg[i]
    lg[i] = lg[i] + (n >= 3 ? -1 : 1)
    i = n + i
  }

  return count
}

console.log('small ' + small())
console.log('big ' + large())
