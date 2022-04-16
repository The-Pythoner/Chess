<!DOCTYPE html>
<html>
<head>
	<title>The Pythoner</title>
	<style>

@font-face {
	font-family: russo;
	src: url("{{url_for('static', filename='russo.ttf')}}");
}

body {
	background-color: #00003f;
	font-family: russo;
	text-align: center;
}

h1 {
	font-size: 60px;
	color: #ffffff;
}

a {
	font-size: 45px;
	color: #003fff;
}

.enddiv {
	padding-bottom: 90px;
}

	</style>
</head>
<body>
	<div class="enddiv">
		<h1>My programs | Mes programmes:</h1>
		<a href="{{url_for('static', filename='chess.zip')}}">Chess</a>
	</div>
	<hr>
	
	<div class="enddiv">
		<h1>My github programs<br>Mes programmes github:</h1>
		<a href="https://github.com/The-Pythoner/Chess" target="_blank">Chess</a>
	</div>
</body>
</html>
