<style>
th {padding: 5px; background-color: #DDDDDD;}td {padding: 5px; min-width: 70px; text-align: center;}td {border-bottom: 1px solid #DDDDDD;}#status{float: right;position: fixed;top: 30px;right: 20px;border: 2px solid #000;padding: 10px;}#upload{float: right;position: fixed;top: 30px;border: 2px solid #000;padding: 10px;left: 20px;}#res{position: fixed;bottom: 10px;width: 80%;background: #DDD;padding: 10px;border-radius: 10px;}
</style>
<?php
// creating soap client
$client = new SoapClient("http://ideone.com/api/1/service.wsdl");
// calling test function
$user="skbly7";
$pass="12345";
$languages = $client->getLanguages($user, $pass);
?>
<form method="post" id="upload">
	<h3>Upload code</h3>
	<textarea rows="10" cols="100" placeholder="Enter code here" name="sourceCode"></textarea>
	<br/><br/>
	<textarea rows="3" cols="100" placeholder="Enter input" name="input"></textarea>
	<br/><br/>
	<select name="language">
	<?php
	foreach($languages['languages'] as $key => $value)
	{
		echo "<option value='".$key."'>".$value."</option>";
	}
	?>
	</select>
	<input type="submit" name="submit" value="Run">
</form>
<br/><br/><br/><br/>
<form method="post" id="status">
	<h3>See status</h3>
	<input type="text" placeholder="Enter ID here" name="link">
	<br/><br/>
	<input type="submit" name="submit2" value="Get status">
</form>
<br/>

<?php
if(isset($_POST['submit']))
{
	$uploaded = $client->createSubmission($user, $pass, $_POST['sourceCode'], $_POST['language'], $_POST['input'], 1, 1);
	echo "<script>alert('Your submission id is : ".$uploaded['link']."');</script>";
}
if(isset($_POST['submit2']))
{
	echo "<div id='res'><h3>Response 
	<form method='post'>
	<input type='text' value='".$_POST['link']."' name='link' hidden>
	<input type='submit' name='submit2' value='Recheck'>
	</form></h3>
	<hr>";
	$result = $client->getSubmissionStatus($user, $pass, $_POST['link']);
	if($result['error']=="OK")
	{
		if($result['status']==3)
			echo "Running...";
		else if($result['status']==1)
			echo "Compiling...";
		else
		{
			$result = $client->getSubmissionDetails($user, $pass, $_POST['link'], 0, 0, 1, 1, 1);
			echo "<pre>".$result['output'].$result['stderr'].$result['cmpinfo']."</pre>";
		}
	}
	else
	{
		echo "Wrong submission ID.";
	}
	echo "</div>";
}
?>