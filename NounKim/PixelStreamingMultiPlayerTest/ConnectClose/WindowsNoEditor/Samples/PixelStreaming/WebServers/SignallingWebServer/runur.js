const { spawn } = require('child_process');
const config = require("./config.json");

module.exports.run = function() {
    const child = spawn(config.urPath, config.urOption);
    child.on('close', (code) => {
        console.log(`ur closed`);
    });
    child.on('exit', (code) => {
        console.log(`ur exit`);
    });

    return child;
}