const fname = '07.txt'
const readf = require('fs').readFileSync

function read(name) {
  return readf(name, {encoding: 'utf8'}).trim()
}

function parse(str) {
  return str
    .split('\n')
    .map(l => {
      let [, name, weight, children] = l.match(/(\w+) \((\d+)\)(?: -> (.+))?/)
      weight = parseInt(weight)
      children = children ? children.split(', ') : []
      return [name, weight, children]
    })
}

function small(nodes) {
  let count = {}
  nodes.forEach(([name, , children]) => {
    count[name] = count[name] === undefined ? 1 : count[name] + 1
    children.forEach(c => count[c] = count[c] === undefined ? 1 : count[name] + 1)
  })
  for (let name in count) {
    if (count[name] === 1) return name
  }
  throw new Error('could not find count of 1')
}

function build(nodes) {
  return nodes.reduce((map, [name, weight, children]) =>
    Object.assign(map, {[name]: {name, weight, children}}), {})
}

function weigh(head, map) {
  const node = map[head]
  if (node.children.length === 0) {
    return node.weight
  }

  let weight
  for (let i = 0; i < node.children.length; i++) {
    let w = weigh(node.children[i], map)
    if (!Number.isInteger(w)) return w
    if (weight === undefined) weight = w
    if (weight !== w) {
      return [weight, node.children.map(c => [c, map[c].weight + map[c].childrenWeight])]
    }
  }

  node.childrenWeight = weight * node.children.length
  return node.weight + node.childrenWeight
}

function large(input, head) {
  const map = build(input)
  const [target, children] = weigh(head, map)
  let [node, w] = children.filter(([c, total]) => total !== target)[0]
  node = map[node]
  return target - node.childrenWeight
}

const input = parse(read(fname))
const head = small(input)
console.log(head)
console.log(large(input, head))
