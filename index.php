<!DOCTYPE html>
<html>
<style>
table, th, td{
    border-width:2px; border-color:black; border-style:solid
}
body{
    background-color: lightgray;
}
select{
    margin-bottom: 25px;
}
div{
    text-align:center;
}
</style>
<body>

<div class="99">
<h1><font align="center" face="Verdana" color = black> Wi-Fi Analysis </font></h1>
<br>
<form method="POST" action = "index.php">
<script language="javascript">
function setValues(){
	var sel = document.getElementById("select1");
	var val = sel.options[sel.selectedIndex].value;
	$.ajax({   
		type: "POST",   
		url: "./index.php",   
		data: { select1: 'val'},
        success: function(jqXHR){
            alert("완료!");
        },
        error: function(jqXHR){}   
	});
}
</script>
<select name = "select1" id="select1">
  <option value=""> 선택 </option>
  <option value="year"> 년 </option>
  <option value="mon"> 월 </option>
  <option value="day"> 일 </option>
  <option value="hour"> 시 </option>
  <option value="min"> 분 </option>
  <option value="sec"> 초 </option>
  <option value="src_ip"> IP </option>
  <option value="src_mac"> MAC </option>
</select>
<input type="text" name="search_data">
<input type="submit" name="제출"><br/>
</form>

<?php
$servername = "localhost";
$username = "root";
$password = "qhdksakstktjd";
$dbname = "wfa";
$select_box = $_POST['select1'];   //select
$values = $_POST['search_data']; //text_box
if($_GET['select1']) $select_box = $_GET['select1'];   //select
if($_GET['search_data']) $values = $_GET['search_data']; //text_box
$posts_num = 15; // 15 per page
$query = "SELECT * from info";
$page_seq = $_GET['page_seq'];

$tmp = $_GET['page_seq'];
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) 
    die("Connection failed: " . $conn->connect_error);

if($select_box != NULL && $values != NULL) {
    $page_num = ceil($total/$posts_num);
    $page_start = $posts_num * $page_seq;

    $sql = "SELECT * FROM info where $select_box='$values' limit $page_start, $posts_num";

    $result2 = $conn->query($sql);
    $total = $result2->num_rows; //전체 수

} 
else {
    $result2 = $conn->query($query);  
    $total = $result2->num_rows; //전체 수 167
    $page_num = ceil($total/$posts_num); // 167/15 = 12
    $page_start = $posts_num * $page_seq; // 12*10 = 120

    $sql = "SELECT * FROM info limit $page_start, $posts_num"; //sql save
}
$result = $conn->query($sql); //query result

echo"검색된 데이터 : $total 건";
?>
<table align="center">

<?php
        echo "<tr>";
        echo "<th>발생 시간</th>";
        echo "<th>IP</th>";
        echo "<th>MAC</th>";
        echo "<th>경로</th>";
        echo "</tr>";

if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
        echo "<tr>";
        echo "<th>" .$row["year"]."." .$row["mon"]."." .$row["day"]." " .$row["hour"].":" .$row["min"].":" .$row["sec"]." " .$row[""]. "<br></th>";
        echo "<th>" .$row["src_ip"]."<br></th>";
        echo "<th>" .$row["src_mac"]."<br></th>";
        echo "<th>" .$row["dl"]."<br></th>";
        echo "</tr>";
    }
} else echo "No such database";
?>
</table>

<?php

$pagegroup_seq = ceil($page_num+1)/5; //2.6

if($pagegroup_seq != 1) {
    if($page_seq > 0) --$page_seq;
    echo "[<a href='$PHP_SELP?page_seq=$page_seq&search_data=$values&select1=$select_box'>이전</a>]  ";
}
    if($page_seq < $page_num-1) ++$tmp;
    echo "  [<a href='$PHP_SELP?page_seq=$tmp&search_data=$values&select1=$select_box'>다음</a>]";
$conn->close();
?>
</body>
</html>