module.exports.aNumber = function aNumber() {
  return 1.75;
};

module.exports.recursiveFibonacci = function recursiveFibonacci(n) {
  if (n < 2) {
    return n;
  }
  return recursiveFibonacci(n - 1) + recursiveFibonacci(n - 2);
};

module.exports.iterativeFibonacci = function iterativeFibonacci(n) {
  if (n < 2) {
    return n;
  }
  let res = 1;
  let prev = 1;
  for (let i = 2; i < n; i++) {
    const temp = res;
    res += prev;
    prev = temp;
  }
  return res;
};

module.exports.Map = Map;

const Rule110Rules = [0, 1, 1, 1, 0, 1, 1, 0]

module.exports.Rule110 = function Rule110(iterations) {
  let states = [];
  let currentCells = new Array(iterations).fill(0);
  currentCells[iterations - 1] = 1;
  states.push(currentCells);
  for (let i = 0; i < iterations - 1; i++) {
    currentCells = currentCells.map((center, index) => {
      const left = index === 0 ? 0 : currentCells[index - 1];
      const right = index === iterations - 1 ? 0 : currentCells[index + 1];
      return Rule110Rules[left << 2 | center << 1 | right];
    });
    states.push(currentCells);
  }
  return states;
}

module.exports.printRule110 = function printRule110(iterations) {
  const states = module.exports.Rule110(iterations);
  for (let i = 0; i < iterations; i++) {
    console.log(states[i].map(cell => cell === 1 ? '█' : ' ').join(''));
  }
}
