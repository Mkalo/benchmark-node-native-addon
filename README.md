# benchmark-node-native-addon

## How to run

```
yarn install
yarn configure // only needed once
yarn build
yarn start
```

## Results

### Returning a number from function
```
NativeModule.aNumber x 30,754,402 ops/sec ±1.16% (93 runs sampled)
JsModule.aNumber x 1,160,106,085 ops/sec ±0.27% (97 runs sampled)
Fastest is JsModule.aNumber
```

### Recursive fibonacci
```
NativeModule.recursiveFibonacci x 630 ops/sec ±1.45% (88 runs sampled)
JsModule.recursiveFibonacci x 134 ops/sec ±1.07% (76 runs sampled)
Fastest is NativeModule.recursiveFibonacci
```

### Iterative fibonacci (native beats js only for large amount of iterations)
```
NativeModule.iterativeFibonacci 100 iterations x 18,004,906 ops/sec ±0.73% (95 runs sampled)
JsModule.iterativeFibonacci 100 iterations x 12,086,964 ops/sec ±0.53% (89 runs sampled)
Fastest is NativeModule.iterativeFibonacci
```

#### For smaller amount of iterations, JS iterative fibonacci is faster
```
NativeModule.iterativeFibonacci 30 iterations x 30,472,767 ops/sec ±1.59% (88 runs sampled)
JsModule.iterativeFibonacci 30 iterations x 69,812,741 ops/sec ±0.83% (92 runs sampled)
Fastest is JsModule.iterativeFibonacci 30 iterations
```

### JS Map vs std::map<string, string>
```
NativeModule.Map x 143 ops/sec ±4.56% (67 runs sampled)
JsModule.Map x 167 ops/sec ±4.12% (67 runs sampled)
Fastest is JsModule.Map
```

### Rule 110
```
NativeModule.Rule110 x 9.85 ops/sec ±1.47% (29 runs sampled)
JsModule.Rule110 x 151 ops/sec ±1.41% (78 runs sampled)
Fastest is JsModule.Rule110
```
JavaScript destroys native here, due to how inefficient it is to create and set values in JS array to return it.

### Rule 110 (printing)
```
NativeModule.printRule110 x 243 ops/sec ±7.83% (21 runs sampled)
JsModule.printRule110 x 143 ops/sec ±8.20% (46 runs sampled)
Fastest is NativeModule.printRule110
```

Here native is faster, since it doesn't have to return anything.


## Conclusions

- Native modules are faster for computationally intensive tasks
- Returning values from native modules is slow, specially if you need to deal with complex JS objects
- Native modules are harder to write and debug
- Trying to use native objects like `std::map` is may not be worth it, since JS objects are good enough if not better (might be different for other containers)
