db.movieDetails.find(
	{'imdb.rating': {$gte: 4.0}, 'imdb.rating': {$lte: 6},
	'tomato.rating': {$gte: 4.0}, 'tomato.rating': {$lte: 6}},
	{_id: 0, title: 1, imdb: 1, tomato: 1});
