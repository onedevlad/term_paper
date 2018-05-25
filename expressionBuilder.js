// SELECT * FROM Table WHERE condition
//   condition:
//     ()
//     !
//     ==, !=, <, >, <=, >=, IS, ISNT, HAS, LT, GT, LTE, GTE
//     &&, AND
//     ||, OR

const condition = '(0 == 0) && ((1) != 0) && 1 == 2'

const specialSymbols = '!=><~&|'

const getPriority = x => {
  if(x == '==') return 1
  if(x == '!=') return 1
  if(x == '>' ) return 1
  if(x == '<' ) return 1
  if(x == '>=') return 1
  if(x == '<=') return 1
  if(x == '~' ) return 1
  if(x == '&&') return 2
  if(x == '||') return 3
  return -1
}

const resolve = (operator, lOperand, rOperand) => {
  console.log("RESOLVE: ", operator, '.', lOperand, '.', rOperand)
  if(operator == '&&') return +lOperand && +rOperand ? 1 : 0
  if(operator == '||') return +lOperand || +rOperand ? 1 : 0
  if(operator == '==') return +lOperand == +rOperand ? 1 : 0
  if(operator == '!=') return +lOperand != +rOperand ? 1 : 0
  if(operator == '<=') return +lOperand <= +rOperand ? 1 : 0
  if(operator == '>=') return +lOperand >= +rOperand ? 1 : 0
  if(operator == '<')  return +lOperand  < +rOperand ? 1 : 0
  if(operator == '>')  return +lOperand  > +rOperand ? 1 : 0
  return 0
}


const bool = query => {
  console.log('BOOL: ', query)

  let hasSpecialSymbols = false
  let cmdPriority = Infinity
  let cmd = []
  let allCmds = []

  let curCmd = ''
  let curCmdStart = 0

  for(let i=0; i<query.length; i++) {
    if(specialSymbols.indexOf(query[i]) > -1) {
      curCmd += query[i]
      hasSpecialSymbols = true
    }
    else {
      if(curCmd != '') {
        let priority = getPriority(curCmd)

        if(priority == -1) {console.log('SYNTAX at ', curCmd)}

        if(priority < cmdPriority) {
          cmdPriority = priority
          cmd = [curCmdStart, i-1]
        }
        allCmds.push(cmd)
      }
      curCmd = ''
      curCmdStart = i+1
    }
  }

  if(hasSpecialSymbols) {
    let lastOperatorEnd = -1
    let nextOperatorStart = query.length

    for(let i=0; i<allCmds.length; i++) {
      if(allCmds[i][0] == cmd[0] && allCmds[i][1] == cmd[1]) continue
      if(allCmds[i][1] > lastOperatorEnd) lastOperatorEnd = allCmds[i][1]
      if(allCmds[i][0] > nextOperatorStart) nextOperatorStart = allCmds[i][0]
    }

    // console.log("LAST: ", lastOperatorEnd)
    // console.log("NEXT: ", nextOperatorStart)

    const lOperand = query.slice(lastOperatorEnd+1, cmd[0])
    const operator = query.slice(cmd[0], cmd[1]+1)
    const rOperand = query.slice(cmd[1]+1, nextOperatorStart)

    // console.log("TOP PRIORITY: ", lOperand + '.' + operator + '.' + rOperand)
    const cmdBefore = query.slice(0, lastOperatorEnd+1)
    const cmdAfter = query.slice(nextOperatorStart, query.length)

    console.log("EXECING: ", `${cmdBefore}.resolve(${operator}, ${lOperand}, ${rOperand}).${cmdAfter}`)
    return bool(`${cmdBefore}${resolve(operator, lOperand, rOperand)}${cmdAfter}`)
  }
  else {
    return query
  }
}

const parser = q => {
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
    // console.log("FINAL: ", bool(query))
    return bool(query)
  }
}

console.log("FINAL: ", parser(condition))