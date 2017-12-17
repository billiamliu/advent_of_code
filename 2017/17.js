function small() {
  const steps = 380
  let buffer = [ 0 ]
  let index = 0
  for (let i = 1; i < 2018; i++) {
    index = (index + steps) % buffer.length + 1
    buffer.splice(index, 0, i)
  }
  return buffer[buffer.indexOf(2017) + 1]
}

function large() {
  const steps = 380
  let bufsize = 1
  let index = 0
  let ans
  for (let i = 1; i < 50000001; i++) {
    index = (index + steps) % bufsize
    if (index === 0) ans = i
    bufsize++
    index++
  }
  return ans
}

console.log(small())
console.log(large())
