const {readFileSync, promises: fsPromises} = require('fs');

// ✅ read file SYNCHRONOUSLY
function syncReadFile(filename) {
  const contents = readFileSync(filename, 'utf-8');

  const arr = contents.split(/\r?\n/);

  // console.log(arr); // 👉️ ['One', 'Two', 'Three', 'Four']

  return arr;
}

function findLocations(locations) {
    const matches = locations[3].match(/\d+/g);
    let positions = []

    for (let i = 0; i < matches.length; i += 2) {
        let position = matches[i] + "." + matches[i+1];
        //console.log(position)
        positions.push(position)
    }

    return positions;
}

const data = syncReadFile('animation.txt');
const positions = findLocations(data);

/*for (let i = 0; i < positions.length; ++i) {
    console.log(positions[i])
}*/

