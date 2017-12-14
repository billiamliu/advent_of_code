const fname = '12.txt'
const readf = require('fs').readFileSync

function read(name) {
  return readf(name, {encoding: 'utf8'}).trim()
}

function parse(str) {
  return str
    .split('\n')
    .map(line => {
      let [num, neighbours] = line.split('<->')
      num = parseInt(num)
      neighbours = neighbours.split(',').map(n => parseInt(n))
      return [num, neighbours]
    })
}

const MAXN = 2000

function dfs(graph, visited, node) {
  let [, neighbours] = graph[node]
  if (visited[node]) return 0
  visited[node] = true
  if (neighbours.length === 0) return 1
  return 1 + neighbours.reduce((acc, n) => acc + dfs(graph, visited, n), 0)
}

function small(input) {
  const visited = []
  for (let i = 0; i < MAXN; i++) {
    visited[i] = false
  }
  return dfs(input, visited, 0)
}

function large(input) {
  const visited = []
  for (let i = 0; i < MAXN; i++) {
    visited[i] = false
  }

  let groupCount = 0
  for (let i = 0; i < MAXN; i++) {
    if (visited[i]) continue
    dfs(input, visited, i)
    groupCount++
  }

  return groupCount
}

console.log(small(parse(read(fname))))
console.log(large(parse(read(fname))))

