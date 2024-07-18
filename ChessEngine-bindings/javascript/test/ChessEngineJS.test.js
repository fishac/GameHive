//import { ChessEngineJS } from './ChessEngineJS.js'

//import * as ChessEngineJS from './ChessEngineJS.js'
//console.log(ChessEngineJS)
//const cejs = await ChessEngineJS();

//console.log(cejs);

/*
const ChessEngineJS = require('./ChessEngineJS.js');
let CEJS;
ChessEngineJS().then((module) => {
	console.log(module);
	CEJS = module;
	console.log(CEJS.getMoveString({from: 1, to: 2, promotionPiece: 0}));
})
*/

const ChessEngineJS = require('./ChessEngineJS.js');

test('import succeeds', () => {
	return ChessEngineJS().then(c => {
		expect(c).toBeTruthy();
	});
});

test('basic functionality', () => {
	return ChessEngineJS().then(ce => {
		expect(ce.getMoveString({from: 0, to: 1, promotionPiece: 0})).toEqual("a1b1");
	});
});