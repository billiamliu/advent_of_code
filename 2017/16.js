const fname = '16.txt'
const readf = require('fs').readFileSync

function read(name) {
  return readf(name, {encoding: 'utf8'}).trim()
}

function parse(str) {
  return str.split(',')
    .map(ins => {
      const c = ins.charAt(0)
      let ret
      switch (c) {
        case 's':
          ret = [c, Number(ins.slice(1))]
          break
        case 'x':
          const [, a, b] = ins.match(/(\d+)\/(\d+)/)
          ret = [c, Number(a), Number(b)]
          break
        case 'p':
          const [, x, y] = ins.match(/p(\w+)\/(\w+)/)
          ret = [c, x, y]
          break
        default:
          throw new Error ('wat')
      }
      return ret
    })
}

function spin(array, dict, n) {
  const ret = []
  const leng = array.length
  const newZero = array.length - n
  for (let i = 0; i < leng; i++) {
    ret[i] = array[(newZero + i) % leng]
    dict[ret[i]] = i
  }
  return ret
}

function exchange(array, dict, j, k) {
  dict[array[j]] = k
  dict[array[k]] = j
  const temp = array[j]
  array[j] = array[k]
  array[k] = temp
}

function partner(array, dict, a, b) {
  exchange(array, dict, dict[a], dict[b])
}

function small(input, progs) {
  progs = progs || [
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
    'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'
  ]
  progs = [...progs]
  const dict = {}
  input.forEach(ins => {
    switch (ins[0]) {
      case 's':
        progs = spin(progs, dict, ins[1])
        break
      case 'x':
        exchange(progs, dict, ins[1], ins[2])
        break
      case 'p':
        partner(progs, dict, ins[1], ins[2])
        break
      default:
        throw new Error('twat')
    }
  })
  return progs
}

function large(input) {
  let p0 = [
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
    'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'
  ]
  const s0 = p0.join('')
  const iter = 1000000000
  for (let i = 0; i < iter; i++) {
    p0 = small(input, p0)
    if (p0.join('') === s0) {
      i = iter - (iter % (i + 1)) - 1
    }
  }
  return p0
}

console.log(small(parse(read(fname))).join(''))
console.log(large(parse(read(fname))).join(''))
