<?php
	include_once 'GraphClass/Graph.php';
	include_once 'GraphClass/Triangle.php';

	include_once 'Algorithms/Deluanay.php';
	include_once 'Algorithms/Dijkstras.php';
	include_once 'Algorithms/Midpoint.php';
	include_once 'Algorithms/TwoStep.php';
	include_once 'Algorithms/ApexAngle.php';
	include_once 'Algorithms/Voronoi.php';

	if (isset($_POST['circles']) && $_POST['circles'] == 1) {
		if (session_id() == "")
			{
			session_start();
		}
		$_SESSION['circles'] = $circles = 1;
	} else {
		$_SESSION['circles'] = $circles = 0;
	}
?>

<head>
	<link type="text/css" rel="stylesheet" href="CSS/topstyle.css" />
</head>
<body>
<?php
	$imagesize = isset($_POST['maxsize']) ? $_POST['maxsize'] : 500;
	$n = isset($_POST['points']) ? $_POST['points'] : 50;
	$graph = new Graph($imagesize);
	$graph2 = new Graph($imagesize);
	for ($i = 1; $i <= $n; $i++) {
		$x = rand(2, $imagesize-2);
		$y = rand(2, $imagesize-2);
		$graph->addVertex( new Vertex($x, $y) );
		$graph2->addVertex( new Vertex($x, $y) );
	}
	$graph->removeDuplicateVertices();
	$graph2->removeDuplicateVertices();
	Deluanay::triangulate($graph);
	$graph2 = clone $graph;
	$pathVertices = $graph->getPathVertices();
	$source = $pathVertices["source"];
	$dest = $pathVertices["dest"];
	echo "<table><tr><td width=".$imagesize.">";
	echo "<font color='yellow'>";
	$algorithm_1 = isset($_POST['algorithm_1']) ? $_POST['algorithm_1'] : "dijkstras";
	switch($algorithm_1) {
		case "deluanay":
			echo "Triangles:   " . count($graph->getTriangles());
			break;
		case "convex":
			$graph->resetEdges();
			$graph->resetTriangles();
			ConvexHull::addHull($graph);
			echo "Hull Vertices:   " . count($graph->getPath());
			break;
		case "dijkstras":
			Dijkstras::addShortestPath($graph, $source, $dest);
			$path = $graph->getPath();
			$cost = 0;
			foreach ($path as $p) 
			{
				$v = $p->getVertices();
				$dist = $v["v1"]->distance($v["v2"]);
				$cost += $dist;
			}
			echo "DIJKSTRAS Path Cost:   " . number_format($cost) . "</br>";
			echo "Intermediate Nodes Visited:   " . (count($path) - 1);
			break;
		case "midpoint":
			Midpoint::addPath($graph, $source, $dest);
			$path = $graph->getPath();
			$cost = 0;
			foreach ($path as $p) {
				$v = $p->getVertices();
				$dist = $v["v1"]->distance($v["v2"]);
				$cost += $dist;
			}
			echo "MIDPOINT Path Cost:   " . number_format($cost) . "</br>";
			echo "Intermediate Nodes Visited:   " . (count($path) - 1);
			break;
		case "twostep":
			TwoStep::addPath($graph, $source, $dest);
			$path = $graph->getPath();
			$cost = 0;
			foreach ($path as $p) {
				$v = $p->getVertices();
				$dist = $v["v1"]->distance($v["v2"]);
				$cost += $dist;
			}
			echo "TWO-STEP Path Cost:   " . number_format($cost) . "</br>";
			echo "Intermediate Nodes Visited:   " . (count($path) - 1);
			break;
		case "apex_angle":
			ApexAngle::addPath($graph, $source, $dest);
			$path = $graph->getPath();
			$cost = 0;
			foreach ($path as $p) {
				$v = $p->getVertices();
				$dist = $v["v1"]->distance($v["v2"]);
				$cost += $dist;
			}
			echo "APEX-ANGLE Path Cost:   " . number_format($cost) . "</br>";
			echo "Intermediate Nodes Visited:   " . (count($path) - 1);
			break;
		case "voronoi_overlay":
			Voronoi::addCells($graph);
			break;
		case "voronoi_only":
			Voronoi::addCells($graph);
			$graph->resetEdges();
			break;
		case "none":
			$graph->resetEdges();
			$graph->resetPath();
			$graph->resetTriangles();
			echo "Unique Nodes:  " . (count($graph->getVertices()));
			break;
	}
	echo "</font>";
	echo "</td> <td width=" . $imagesize . ">";
	echo "<font color='red'>";
	$algorithm_2 = isset($_POST['algorithm_2']) ? $_POST['algorithm_2'] : "deluanay";
	switch($algorithm_2) {
		case "off":
			break;
		case "deluanay":
			echo "Triangles:   " . count($graph2->getTriangles());
			break;
		case "convex":
			$graph2->resetEdges();
			$graph2->resetTriangles();
			ConvexHull::addHull($graph2);
			echo "Hull Vertices:   " . count($graph2->getPath());
			break;
		case "dijkstras":
			Dijkstras::addShortestPath($graph2, $source, $dest);
			$path = $graph2->getPath();
			$cost = 0;
			foreach ($path as $p) {
				$v = $p->getVertices();
				$dist = $v["v1"]->distance($v["v2"]);
				$cost += $dist;
			}
			echo "DIJKSTRAS Path Cost:   " . number_format($cost) . "</br>";
			echo "Intermediate Nodes Visited:   " . (count($path) - 1);
			break;
		case "midpoint":
			Midpoint::addPath($graph2, $source, $dest);
			$path = $graph2->getPath();
			$cost = 0;
			foreach ($path as $p) {
				$v = $p->getVertices();
				$dist = $v["v1"]->distance($v["v2"]);
				$cost += $dist;
			}
			echo "MIDPOINT Path Cost:   " . number_format($cost) . "</br>";
			echo "Intermediate Nodes Visited:   " . (count($path) - 1);
			break;
		case "twostep":
			TwoStep::addPath($graph2, $source, $dest);
			$path = $graph2->getPath();
			$cost = 0;
			foreach ($path as $p) {
				$v = $p->getVertices();
				$dist = $v["v1"]->distance($v["v2"]);
				$cost += $dist;
			}
			echo "TWO-STEP Path Cost:   " . number_format($cost) . "</br>";
			echo "Intermediate Nodes Visited:   " . (count($path) - 1);
			break;
		case "apex_angle":
			ApexAngle::addPath($graph2, $source, $dest);
			$path = $graph2->getPath();
			$cost = 0;
			foreach ($path as $p) {
				$v = $p->getVertices();
				$dist = $v["v1"]->distance($v["v2"]);
				$cost += $dist;
			}
			echo "APEX-ANGLE Path Cost:   " . number_format($cost) . "</br>";
			echo "Intermediate Nodes Visited:   " . (count($path) - 1);
			break;
		case "voronoi_overlay":
			Voronoi::addCells($graph2);
			break;
		case "voronoi_only":
			Voronoi::addCells($graph2);
			$graph2->resetEdges();
			break;
		case "none":
			$graph2->resetEdges();
			$graph2->resetPath();
			$graph2->resetTriangles();
			echo "Unique Nodes:  " . (count($graph2->getVertices()));
			break;
	}
	echo "</font>";
	echo "</tr><tr><td width=".$imagesize.">";
	$graph->display_a();
	if ($algorithm_2 != "off") {
		echo "</td><td width=".$imagesize.">";
		$graph2->display_b();
	}
	echo "</td></tr></table>";
?>
</br>
<form name="regenerate" action="results.php" method="post">
	<input type="hidden" name="maxsize" value=<?php echo $imagesize ?> >
	<input type="hidden" name="points" value=<?php echo $n ?> >
	<input type="hidden" name="circles" value=<?php echo $circles ?> >
	<input type="hidden" name="algorithm_1" value=<?php echo $algorithm_1 ?> >
	<input type="hidden" name="algorithm_2" value=<?php echo $algorithm_2 ?> >
	<input class="button" value="RE-GENERATE" type="submit">
</form>
<form name="back" action="main.php" method="post">
	<input class="button" value="BACK TO FORM" type="submit">
</form>
</body>
