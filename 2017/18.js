const fname = '18.txt'
const readf = require('fs').readFileSync

function read(name) {
  return readf(name, {encoding: 'utf8'}).trim()
}

function parse(str) {
  return str.split('\n').map(l => {
    let [ins, reg, val] = l.split(' ')
    val = Number.isInteger(Number(val)) ? Number(val) : val
    return [ins, reg, val]
  })
}

function small(input) {
  const regs = {out: 0}
  recovered = null
  for (let i = 0; i < input.length; i++) {
    if (recovered !== null) break
    const [ins, reg, val] = input[i]
    switch (ins) {
      case 'snd':
        regs['out'] = regs[reg]
        break
      case 'set':
        regs[reg] = Number.isInteger(val) ? val : regs[val]
        break
      case 'add':
        regs[reg] += Number.isInteger(val) ? val : regs[val]
        break
      case 'mul':
        regs[reg] *= Number.isInteger(val) ? val : regs[val]
        break
      case 'mod':
        regs[reg] %= Number.isInteger(val) ? val : regs[val]
        break
      case 'rcv':
        if (regs[reg] !== 0) {
          recovered = regs['out']
        }
        break
      case 'jgz':
        if (regs[reg] > 0) {
          i += Number.isInteger(val) ? val : regs[val]
          i--
        }
        break
      default:
        console.error(i, input[i])
        throw new Error('wat')
    }
  }
  return recovered
}

function simulate(input, p, q, outbox) {
  let [ins, reg, val] = input[p.index]
  if (ins === 'rcv') {
    if (q.length === 0) {
      p.waiting = true
      return
    } else {
      p.waiting = false
      p[reg] = q.shift()
      p.index++
      return
    }
  }

  if (ins === 'jgz') {
    if (Number(reg) || p[reg] > 0) {
      p.index += Number.isInteger(val) ? val : p[val]
    } else {
      p.index++
    }
    return
  }

  switch (ins) {
    case 'snd':
      outbox.push(p[reg] || 0)
      p.sent++
      break
    case 'set':
      p[reg] = Number.isInteger(val) ? val : p[val]
      break
    case 'add':
      p[reg] += Number.isInteger(val) ? val : p[val]
      break
    case 'mul':
      p[reg] *= Number.isInteger(val) ? val : p[val]
      break
    case 'mod':
      p[reg] %= Number.isInteger(val) ? val : p[val]
      break
    default:
      console.error(p.index, input[p.index])
      throw new Error('wat')
  }
  p.index++
}

function large(input) {
  const p0 = {waiting: false, sent: 0, index: 0, p: 0}
  const q0 = []
  const p1 = {waiting: false, sent: 0, index: 0, p: 1}
  const q1 = []

  while (
    p0.index >= 0 && p0.index < input.length &&
    p1.index >= 0 && p1.index < input.length
  ) {
    if (p0.waiting && p1.waiting && q0.length === 0 && q1.length === 0) { break }
    simulate(input, p0, q0, q1)
    simulate(input, p1, q1, q0)
  }
  return p1.sent
}

console.log(small(parse(read(fname))))
console.log(large(parse(read(fname))))
