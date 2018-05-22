// SELECT * FROM Table WHERE condition
//   condition:
//     ()
//     !
//     ==, !=, <, >, <=, >=, IS, ISNT, HAS, LT, GT, LTE, GTE
//     &&, AND
//     ||, OR

// const condition = '(0 == 0) && ((1) != 0) && 1 == 2'
const condition = '(0 == 0) || ((1) != 0) && 1 == 2'

const specialSymbols = '!=><~&|'

const priorityList = {
  '==': 0,
  '!=': 0,
  '>': 0,
  '<': 0,
  '<=': 0,
  '>=': 0,
  '~': 0,
  '&&': 1,
  '||': 2,
}

const resolve = (operator, lOperand, rOperand) => {
  // console.log("RESOLVE: ", operator, '.', lOperand, '.', rOperand)
  if(operator == '&&') return +lOperand && +rOperand ? 1 : 0
  if(operator == '||') return +lOperand || +rOperand ? 1 : 0
  if(operator == '==') return +lOperand == +rOperand ? 1 : 0
  if(operator == '!=') return +lOperand != +rOperand ? 1 : 0
  return 0
}

let cntr =0
const bool = query => {
  // console.log('BOOL: ', query)

  let cmds = [[], [], []]

  let hasSpecialSymbols = false

  for(let i=0; i<query.length; i++) {
    if(query[i] == '=' && query[i+1] == '=') { cmds[priorityList['==']].push([i, i+1]); hasSpecialSymbols = true; i++}
    if(query[i] == '!' && query[i+1] == '=') { cmds[priorityList['!=']].push([i, i+1]); hasSpecialSymbols = true; i++}
    if(query[i] == '&' && query[i+1] == '&') { cmds[priorityList['&&']].push([i, i+1]); hasSpecialSymbols = true; i++}
    if(query[i] == '|' && query[i+1] == '|') { cmds[priorityList['||']].push([i, i+1]); hasSpecialSymbols = true; i++}
    if(query[i] == '>' && query[i+1] == '=') { cmds[priorityList['>=']].push([i, i+1]); hasSpecialSymbols = true; i++}
    if(query[i] == '<' && query[i+1] == '=') { cmds[priorityList['<=']].push([i, i+1]); hasSpecialSymbols = true; i++}
    if(query[i] == '<') { cmds[priorityList['<']].push([i, i]); hasSpecialSymbols = true }
    if(query[i] == '>') { cmds[priorityList['>']].push([i, i]); hasSpecialSymbols = true }
    if(query[i] == '~') { cmds[priorityList['~']].push([i, i]); hasSpecialSymbols = true }
  }

  if(hasSpecialSymbols) {
    for(let i=0; i<cmds.length; i++) {
      for(let j=0; j<cmds[i].length; j++) {
        let lastOperator = [-1, -1]
        let nextOperator = [query.length, query.length]
        for(let k=cmds[i][j][0]-1; k>0; k--) {
          if(specialSymbols.indexOf(query[k]) > -1) {
            lastOperator = [k, k]
            if(specialSymbols.indexOf(query[k-1]) > -1) {
              lastOperator = [k-1, k]
            }
            break
          }
        }
        for(let k=cmds[i][j][1]+1; k<query.length+1; k++) {
          if(specialSymbols.indexOf(query[k]) > -1) {
            nextOperator = [k,k]
            if(specialSymbols.indexOf(query[k+1]) > -1) {
              nextOperator = [k, k+1]
            }
            break
          }
        }
        const lOperand = query.slice(lastOperator[1]+1, cmds[i][j][0])
        const operator = query.slice(cmds[i][j][0], cmds[i][j][1]+1)
        const rOperand = query.slice(cmds[i][j][1]+1, nextOperator[0])

        // console.log("TOP PRIORITY: ", lOperand + operator + rOperand)
        const cmdBefore = query.slice(0, lastOperator[1]+1)
        const cmdAfter = query.slice(nextOperator[0], query.length)

        // console.log("EXECING: ", `${cmdBefore}.${resolve(operator, lOperand, rOperand)}.${cmdAfter}`)
        return bool(`${cmdBefore}${resolve(operator, lOperand, rOperand)}${cmdAfter}`)
      }
    }
  } else {
    return query
  }
}

const parser = q => {
  let parenthesis = []

  let openParenthesis = []


  const query = q.replace(/\s/g, '')
  console.log('QUERY: ', query)

  let lvl = -1

  let deepestLvl = -1;
  let deepest;

  if(query.indexOf('(') > -1) {
    for(let i=0; i< query.length; i++) {
      if(query[i] === '(') {
        lvl++
        openParenthesis.push(i)
      }
      if(query[i] === ')') {
        if(lvl > deepestLvl) {
          deepest = [openParenthesis.pop(), i]
          deepestLvl = lvl
        }
        lvl--
      }
    }
    const cmdBefore = query.slice(0, deepest[0])
    const cmd = query.slice(deepest[0]+1, deepest[1])
    const cmdAfter = query.slice(deepest[1] + 1, query.length)
    // console.log(cmdBefore, '.', cmd, '.', cmdAfter)
    return parser(`${cmdBefore}${bool(cmd)}${cmdAfter}`)
  }
  else {
    // Linear query here
    console.log("FINAL: ", bool(query))
  }

  return '1'
}

parser(condition)