const {readFileSync, promises: fsPromises} = require('fs');

// ✅ read file SYNCHRONOUSLY
function syncReadFile(filename) {
  const contents = readFileSync(filename, 'utf-8');

  const arr = contents.split(/\r?\n/);

  // console.log(arr); // 👉️ ['One', 'Two', 'Three', 'Four']

  return arr;
}

/*export function findMoves() {
    const locations = syncReadFile('asdfsad.txt');
    let positions = [];

    for (let i = 0; i < locations.length; ++i) {
        const matches = locations[i].match(/\d+/g);
        positions.push([matches[0], matches[1], matches[2], matches[3]]);
    }

    return positions;
}*/

//console.log(findMoves());

/*for (let i = 0; i < positions.length; ++i) {
    console.log(positions[i])
}*/



