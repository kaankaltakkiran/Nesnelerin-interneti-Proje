<?php
// Config dosyasını dahil et
require_once __DIR__ . '/config.php';

// Veritabanı bağlantısı
$conn = new mysqli(DB_SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);

// Bağlantı kontrolü
if ($conn->connect_error) {
    die("Bağlantı başarısız: " . $conn->connect_error);
}

// Röle durumunu değiştirme
if (isset($_POST['toggle'])) {
    // Mevcut durumu tersine çevir
    $status = $_POST['status'] == 1 ? 0 : 1;
    $sql = "UPDATE nodemcu SET relay_status = $status WHERE id = 1";

    if ($conn->query($sql) === TRUE) {
        echo "Priz durumu başarıyla değiştirildi.";
    } else {
        echo "Hata: " . $sql . "<br>" . $conn->error;
    }
}

// Mevcut röle durumunu al
$sql = "SELECT relay_status FROM nodemcu WHERE id = 1";
$result = $conn->query($sql);
$row = $result->fetch_assoc();
$relayStatus = $row['relay_status'];

$conn->close();
?>


<!DOCTYPE html>
<html lang="tr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Priz Kontrol</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #f3f4f6;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            min-height: 100vh;
            color: #333;
        }
        h1 {
            font-size: 2rem;
            margin-bottom: 20px;
            color: #2d3748;
        }
        form {
            display: flex;
            flex-direction: column;
            align-items: center;
        }
        button {
            background-color: #4CAF50;
            color: white;
            border: none;
            padding: 10px 20px;
            font-size: 1.2rem;
            border-radius: 5px;
            cursor: pointer;
            transition: background-color 0.3s;
        }
        button:hover {
            background-color: #45a049;
        }
        @media (max-width: 768px) {
            h1 {
                font-size: 1.5rem;
            }
            button {
                font-size: 1rem;
                padding: 8px 16px;
            }
        }
        footer {
            margin-top: 20px;
            font-size: 0.9rem;
            color: #555;
        }
    </style>
</head>
<body>
    <h1>Priz Durumu: <?php echo $relayStatus == 1 ? 'Açık' : 'Kapalı'; ?></h1>
    <form method="post">
        <input type="hidden" name="status" value="<?php echo $relayStatus; ?>">
        <button type="submit" name="toggle"><?php echo $relayStatus == 1 ? 'Prizi Kapat' : 'Prizi Aç'; ?></button>
    </form>
    <footer>
        © Kaan Kaltakkıran  2025 Priz Kontrol - Tüm hakları saklıdır.
    </footer>
</body>
</html>

