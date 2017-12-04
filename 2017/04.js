// small
document.body.innerText.split('\n')
  .reduce((sum, line) => {
    if (!line.length) return sum
    let mySet = new Set()
    let hasDupe = line
      .split(' ')
      .reduce((s, w) => {
        if (mySet.has(w)) return s + 1
        else {
          mySet.add(w)
          return s
        }
      }, 0)
    return hasDupe ? sum + 0 : sum + 1
  }, 0)

// large
document.body.innerText.split('\n')
  .reduce((sum, line) => {
    if (!line.length) return sum
    let mySet = new Set()
    let hasDupe = line
      .split(' ')
      .reduce((s, w) => {
        w = w.split('').sort().join('')
        if (mySet.has(w)) return s + 1
        else {
          mySet.add(w)
          return s
        }
      }, 0)
    return hasDupe ? sum + 0 : sum + 1
  }, 0)
