const fname = '08.txt'
const readf = require('fs').readFileSync

function read(name) {
  return readf(name, {encoding: 'utf8'}).trim()
}

function parse(str) {
  return str
    .split('\n')
    .map(l => {
      let [, dest, op, n, reg, cond, k] = l.match(/(\w+) (\w+) (\-?\d+) if (\w+) (\W{1,2}) (\-?\d+)/)
      n = parseInt(n)
      // k = parseInt(k) not parsing this one, using as string literal
      return [dest, op, n, reg, cond, k]
    })
}

function run(input) {
  const map = {}
  let allTimeMax = 0
  input.forEach(([dest, op, n, reg, cond, k]) => {
    if (map[dest] === undefined) map[dest] = 0
    if (map[reg] === undefined) map[reg] = 0

    const ans = eval(`${map[reg]} ${cond} ${k}`)

    if (ans) {
      map[dest] = op === 'inc' ? map[dest] + n : map[dest] - n
    }

    if (map[dest] > allTimeMax) allTimeMax = map[dest]
  })

  let max = 0
  for (let k in map) {
    if (map[k] > max) {
      max = map[k]
    }
  }

  return [max, allTimeMax]
}

const input = parse(read(fname))
console.log(run(input))
