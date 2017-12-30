const fname = '23.txt'
const readf = require('fs').readFileSync

function read(name) {
  return readf(name, {encoding: 'utf8'}).trim()
}

function parse(str) {
  return str.split('\n').map(l => {
    let [, ins, reg, val] = l.match(/(\w+)\s(\w)\s(.+)/)
    reg = Number.isInteger(Number(reg)) ? Number(reg) : reg
    val = Number.isInteger(Number(val)) ? Number(val) : val
    return [ins, reg, val]
  })
}

function small(regs, input) {
  let count = 0
  let i = 0
  while (i < input.length) {
    const [ins, reg, val] = input[i]
    switch (ins) {
      case 'set':
        regs[reg] = Number.isInteger(val) ? val : regs[val]
        break
      case 'sub':
        regs[reg] -= Number.isInteger(val) ? val : regs[val]
        break
      case 'mul':
        count++
        regs[reg] *= Number.isInteger(val) ? val : regs[val]
        break
      case 'jnz':
        debugger
        if (reg === 1 || regs[reg] !== 0) {
          i += val
          continue
        }
        break
    }
    i++
  }
  return [count, regs]
}

function large(input) {
  const regs = { b: 93, c: 93, d: 0, f: 0, g: 0, h: 0 }
  regs['b'] = regs['b'] * 100 + 100000
  regs['c'] = regs['b'] + 17000
  do {
    regs['f'] = 1
    regs['d'] = 2
    for (let d = regs['d']; d * d < regs['b']; d++) {
      if (regs['b'] % d === 0) {
        regs['f'] = 0
        break
      }
    }
    if (regs['f'] === 0) regs['h']++
    regs['g'] = regs['b'] - regs['c']
    regs['b'] += 17
  } while (regs['g'] !== 0)

  return regs['h']
}

console.log(small({ a: 0, b: 0, c: 0, d: 0, e: 0, f: 0, g: 0, h: 0 },parse(read(fname))))
console.log(large(parse(read(fname))))
