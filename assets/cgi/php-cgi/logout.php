<?php
session_start();
session_unset();
session_destroy();

echo "<h1>Logged out!</h1>";
echo "<a href='/php-cgi/session_start.php'>back</a>";