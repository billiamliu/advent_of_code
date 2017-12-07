const input = [0, 5, 10, 0, 11, 14, 13, 4, 11, 8, 8, 7, 1, 4, 12, 11]

function redistribute(array, source) {
  const size = array.length
  let count = array[source]
  array[source++] = 0

  while (count--) {
    if (source == size) {
      source = 0
    }
    array[source++]++
  }

  return count
}

function maxIndex(array) {
  let i = 0
  let max = 0
  array.forEach((ele, idx) => {
    if (ele > max) {
      i = idx
      max = ele
    }
  })

  return i
}

function step(array) {
  let max = maxIndex(array)
  redistribute(array, max)
  return array.join(' ')
}

function run(array) {
  const cache = {}
  let count = 0
  let key

  while (!(key in cache)) {
    cache[key] = count
    key = step(array)
    count++
  }

  return [count, count - cache[key]]
}

console.log(run(input))
