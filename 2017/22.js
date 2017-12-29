const fname = '22.txt'
const readf = require('fs').readFileSync

function read(name) {
  return readf(name, {encoding: 'utf8'}).trim()
}

function parse(str) {
  const grid = str.split('\n').map(line => line.split('').map(c => c === '.' ? 0 : 1))
  const size = grid.length
  const ret = {}
  for (let y = 0; y < size; y++) {
    for (let x = 0; x < size; x++) {
      ret[`${x},${y}`] = grid[y][x]
    }
  }
  return ret
}

function turnRight(dir) {
  let temp = dir[0]
  dir[0] = dir[1]
  dir[1] = temp * -1
  return dir
}

function turnLeft(dir) {
  let temp = dir[0]
  dir[0] = dir[1] * -1
  dir[1] = temp
  return dir
}

function reverse(dir) {
  dir[0] *= -1
  dir[1] *= -1
  return dir
}

function small(grid, width, height) {
  let x = width >> 1
  let y = height >> 1
  let dir = [0, 1]
  let infectCount = 0
  for (let i = 0; i < 10000; i++) {
    const key = `${x},${y}`
    if (grid[key] === 1) {
      turnRight(dir)
      grid[key] = 0
    } else {
      turnLeft(dir)
      grid[key] = 1
      infectCount++
    }
    x += dir[0]
    y -= dir[1]
  }
  return infectCount
}

function large(grid, size) {
  // 0 clean,  1 infected, 2 weakened, 3 flagged
  let x = size >> 1
  let y = x
  let dir = [0, 1]
  let infectCount = 0
  for (let i = 0; i < 10000000; i++) {
    const key = `${x},${y}`
    if (grid[key] === undefined) grid[key] = 0
    switch (grid[key]) {
      case 1:
        grid[key] = 3
        turnRight(dir)
        break
      case 0:
        grid[key] = 2
        turnLeft(dir)
        break
      case 2:
        grid[key] = 1
        infectCount++
        break
      case 3:
        grid[key] = 0
        reverse(dir)
        break
    }
    x += dir[0]
    y -= dir[1]
  }
  return infectCount
}

let grid = parse(read(fname))
console.log( small( grid, 25, 25 ) )
grid = parse(read(fname))
console.log( large( grid, 25 ) )
