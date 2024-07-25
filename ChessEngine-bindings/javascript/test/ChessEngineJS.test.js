const ChessEngineJS = require('./ChessEngineJS.js');

test('import succeeds', () => {
	return ChessEngineJS().then(ce => {
		expect(ce).toBeTruthy();
	});
});

test('top level contents', () => {
	return ChessEngineJS().then(ce => {
		expect(typeof ce.getMoveString).toBe("function");
		expect(typeof ce.BoardState).toBe("function");
		expect(typeof ce.ChessEngine).toBe("function");
	});
});

test('BoardState definition', () => {
	return ChessEngineJS().then(ce => {
		const bs = new ce.BoardState(true);
		expect(bs).toBeTruthy();
		
		expect(bs.setFEN).toBeTruthy()
		expect(bs.isLegalFromSquare).toBeTruthy()
		expect(bs.getLegalMoves).toBeTruthy()
		expect(bs.getLegalMovesFromSquare).toBeTruthy()
		expect(bs.makeMove).toBeTruthy()
		expect(bs.isMoveLegal).toBeTruthy()
		expect(bs.getCheckStatus).toBeTruthy()
		expect(bs.getCheckmateStatus).toBeTruthy()
		expect(bs.getStalemateStatus).toBeTruthy()
		expect(bs.isDrawByRepitition).toBeTruthy()
		expect(bs.isDrawByInsufficientMaterial).toBeTruthy()
		expect(bs.getTurnColor).toBeTruthy()
		expect(bs.getWhiteKingSquare).toBeTruthy()
		expect(bs.getBlackKingSquare).toBeTruthy()
		expect(bs.getPieceOnSquareIdx).toBeTruthy()
		expect(bs.getColorOnSquareIdx).toBeTruthy()
		expect(bs.isSquareOccupied).toBeTruthy()
		
		expect(typeof bs.setFEN).toBe("function")
		expect(typeof bs.isLegalFromSquare).toBe("function")
		expect(typeof bs.getLegalMoves).toBe("function")
		expect(typeof bs.getLegalMovesFromSquare).toBe("function")
		expect(typeof bs.makeMove).toBe("function")
		expect(typeof bs.isMoveLegal).toBe("function")
		expect(typeof bs.getCheckStatus).toBe("function")
		expect(typeof bs.getCheckmateStatus).toBe("function")
		expect(typeof bs.getStalemateStatus).toBe("function")
		expect(typeof bs.isDrawByRepitition).toBe("function")
		expect(typeof bs.isDrawByInsufficientMaterial).toBe("function")
		expect(typeof bs.getTurnColor).toBe("function")
		expect(typeof bs.getWhiteKingSquare).toBe("function")
		expect(typeof bs.getBlackKingSquare).toBe("function")
		expect(typeof bs.getPieceOnSquareIdx).toBe("function")
		expect(typeof bs.getColorOnSquareIdx).toBe("function")
		expect(typeof bs.isSquareOccupied).toBe("function")
	});
});

test('ChessEngine definition', () => {
	return ChessEngineJS().then(ce => {
		const eng = new ce.ChessEngine();
		expect(eng).toBeTruthy();
		
		expect(eng.suggestMove).toBeTruthy();
		expect(eng.provideMove).toBeTruthy();
		expect(eng.setFEN).toBeTruthy();
		expect(eng.getMoveSearchDepth).toBeTruthy();
		expect(eng.getMoveSearchTime).toBeTruthy();
		expect(eng.getMoveSearchTimeLimit).toBeTruthy();
		expect(eng.searchWasHardTimeCutoff).toBeTruthy();
		expect(eng.getNumScannedNodes).toBeTruthy();
		
		expect(typeof eng.suggestMove).toBe("function");
		expect(typeof eng.provideMove).toBe("function");
		expect(typeof eng.setFEN).toBe("function");
		expect(typeof eng.getMoveSearchDepth).toBe("function");
		expect(typeof eng.getMoveSearchTime).toBe("function");
		expect(typeof eng.getMoveSearchTimeLimit).toBe("function");
		expect(typeof eng.searchWasHardTimeCutoff).toBe("function");
		expect(typeof eng.getNumScannedNodes).toBe("function");
	});
});

test('getMoveString and Move basic functionality', () => {
	return ChessEngineJS().then(ce => {
		expect(ce.getMoveString({from: 0, to: 1, promotionPiece: 0})).toEqual("a1b1");
		expect(ce.getMoveString({from: 0, to: 8, promotionPiece: 0})).toEqual("a1a2");
		expect(ce.getMoveString({from: 20, to: 29, promotionPiece: 0})).toEqual("e3f4");
		expect(ce.getMoveString({from: 55, to: 63, promotionPiece: 0})).toEqual("h7h8");
		expect(ce.getMoveString({from: 55, to: 63, promotionPiece: 2})).toEqual("h7h8=N");
		expect(ce.getMoveString({from: 55, to: 63, promotionPiece: 3})).toEqual("h7h8=B");
		expect(ce.getMoveString({from: 55, to: 63, promotionPiece: 4})).toEqual("h7h8=R");
		expect(ce.getMoveString({from: 55, to: 63, promotionPiece: 5})).toEqual("h7h8=Q");
		expect(() => {
			ce.getMoveString()
		}).toThrow();
		expect(() => {
			ce.getMoveString({})
		}).toThrow();
		expect(() => {
			ce.getMoveString({from: 0})
		}).toThrow();
		expect(() => {
			ce.getMoveString({to: 0})
		}).toThrow();
		expect(() => {
			ce.getMoveString({from: 0, to: 0})
		}).toThrow();
	});
});

test('BoardState functionality', () => {
	return ChessEngineJS().then(ce => {
		const bs = new ce.BoardState(true);

		expect(bs.isLegalFromSquare(8)).toBe(true);
		expect(bs.isLegalFromSquare(0)).toBe(false);

		expect(bs.getLegalMoves()).toBeTruthy();
		expect(typeof bs.getLegalMoves()).toBe("object");
		expect(bs.getLegalMoves().size()).toBe(20);
		const legalMovesArray = new Array(bs.getLegalMoves().size()).fill(0).map((_, id) => bs.getLegalMoves().get(id));
		expect(legalMovesArray.some(m => (
			m.from === 8 && m.to === 16 && m.promotionPiece === 0
		))).toBe(true);
	});
});