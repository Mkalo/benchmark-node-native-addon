const NativeModule = require("./build/Release/NativeModule.node");
const JsModule = require("./JsModule.js");
const Benchmark = require("benchmark");
const crypto = require("crypto");

let gc = global.gc || (() => {});

function setupAndRunSuite(suite) {
  return suite
    .on("setup", () => {
      gc();
    })
    .on("cycle", (event) => {
      console.log(String(event.target));
    })
    .on("complete", () => {
      console.log("Fastest is " + suite.filter("fastest").map("name"));
    })
    .run();
}
setupAndRunSuite.skip = () => {};

setupAndRunSuite(
  new Benchmark.Suite()
    .add("NativeModule.aNumber", () => {
      NativeModule.aNumber();
    })
    .add("JsModule.aNumber", () => {
      JsModule.aNumber();
    })
);

setupAndRunSuite(
  new Benchmark.Suite()
    .add("NativeModule.recursiveFibonacci", () => {
      NativeModule.recursiveFibonacci(30);
    })
    .add("JsModule.recursiveFibonacci", () => {
      JsModule.recursiveFibonacci(30);
    })
);

setupAndRunSuite(
  new Benchmark.Suite()
    .add("NativeModule.iterativeFibonacci 100 iterations", () => {
      NativeModule.iterativeFibonacci(100);
    })
    .add("JsModule.iterativeFibonacci 100 iterations", () => {
      JsModule.iterativeFibonacci(100);
    })
);

setupAndRunSuite(
  new Benchmark.Suite()
    .add("NativeModule.iterativeFibonacci 30 iterations", () => {
      NativeModule.iterativeFibonacci(30);
    })
    .add("JsModule.iterativeFibonacci 30 iterations", () => {
      JsModule.iterativeFibonacci(30);
    })
);

setupAndRunSuite(
  new Benchmark.Suite()
    .add("NativeModule.Map", () => {
      const map = new NativeModule.Map();
      const N = 1000;
      const keys = Array.from({ length: N }, () =>
        crypto.randomBytes(16).toString("hex")
      );
      const values = Array.from({ length: N }, () =>
        crypto.randomBytes(16).toString("hex")
      );

      for (let i = 0; i < N; i++) {
        map.set(keys[i], values[i]);
      }

      for (let i = 0; i < N; i++) {
        map.has(keys[i]);
        map.get(keys[i]);
        map.delete(keys[i]);
      }
    })
    .add("JsModule.Map", () => {
      const map = new JsModule.Map();
      const N = 1000;
      const keys = Array.from({ length: N }, () =>
        crypto.randomBytes(16).toString("hex")
      );
      const values = Array.from({ length: N }, () =>
        crypto.randomBytes(16).toString("hex")
      );
      for (let i = 0; i < N; i++) {
        map.set(keys[i], values[i]);
      }

      for (let i = 0; i < N; i++) {
        map.has(keys[i]);
        map.get(keys[i]);
        map.delete(keys[i]);
      }
    })
);

setupAndRunSuite(
  new Benchmark.Suite()
    .add("NativeModule.Rule110", () => {
      NativeModule.Rule110(1000);
    })
    .add("JsModule.Rule110", () => {
      JsModule.Rule110(1000);
    })
);

setupAndRunSuite(
  new Benchmark.Suite()
    .add("NativeModule.printRule110", () => {
      NativeModule.printRule110(100);
    })
    .add("JsModule.printRule110", () => {
      JsModule.printRule110(100);
    })
);
