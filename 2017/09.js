const fname = '09.txt'
const readf = require('fs').readFileSync

function read(name) {
  return readf(name, {encoding: 'utf8'}).trim()
}

function run(str) {
  let stack = 0
  let i = 0
  let isGarb = false
  let sum = 0
  let garb = 0
  while (i < str.length) {
    let c = str.charAt(i++)
    if (c === '!') i++
    if (isGarb && c !== '>') {
      if (c !== '!') garb++
      continue
    }
    switch (c) {
      case '{':
        stack++
        sum += stack
        break
      case '}':
        stack--
        break
      case '<':
        isGarb = true
        break
      case '>':
        isGarb = false
        break
      default:
        break
    }
  }

  return [sum, garb]
}

console.log(run(read(fname)))
