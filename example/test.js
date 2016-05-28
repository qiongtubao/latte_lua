var addon = require('../build/Release/latte.node');
//('hello');

console.log(addon.doFileSync("./test.lua", "add", 2,2,3)); // 'world'
console.log(addon.doFileSync("./test.lua", "join", 2, "a", "b"));
console.log(addon.doFileSync("./test.lua", "isOK", 1, false));
console.log(addon.doFileSync("./test.lua", "array",2, [1,2,3], [8,9,10]));
console.log(addon.doFileSync("./test.lua", "t", 2, {a: 1}, {b:2}));
console.log(addon.doFileSync("./test.lua", "get", 0));
console.log(addon.doFileSync("./test.lua", "set", 1, {a: {b: "c"}}));
