-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Waktu pembuatan: 24 Bulan Mei 2022 pada 12.36
-- Versi server: 10.4.14-MariaDB
-- Versi PHP: 7.2.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `smartaquascape`
--

-- --------------------------------------------------------

--
-- Struktur dari tabel `monitoring`
--

CREATE TABLE `monitoring` (
  `id` int(11) NOT NULL,
  `temperature` varchar(255) NOT NULL,
  `water_level` varchar(255) NOT NULL,
  `turbidity` varchar(255) NOT NULL,
  `request_time` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `monitoring`
--

INSERT INTO `monitoring` (`id`, `temperature`, `water_level`, `turbidity`, `request_time`) VALUES
(1, '30.88', '23.00', '3003.27', '2022-05-21 18:53:07'),
(2, '30.88', '23.00', '3003.27', '2022-05-21 18:53:50'),
(3, '31', '2.00', '2755.27', '2022-05-21 18:53:50'),
(4, '31', '2.00', '2755.27', '2022-05-22 07:47:30'),
(5, '31', '2.00', '2755.27', '2022-05-22 07:48:11'),
(6, '31', '2.00', '2755.27', '2022-05-22 07:48:11'),
(7, '31', '2.00', '2755.27', '2022-05-22 07:48:11'),
(8, '31', '2.00', '2755.27', '2022-05-22 07:48:12'),
(9, '31', '2.00', '2755.27', '2022-05-22 07:48:12'),
(10, '31', '2.00', '2755.27', '2022-05-22 07:48:12'),
(11, '31', '2.00', '2755.27', '2022-05-22 07:48:13'),
(12, '31', '2.00', '2755.27', '2022-05-22 07:48:13'),
(13, '31', '2.00', '2755.27', '2022-05-22 07:48:13'),
(14, '31', '2.00', '2755.27', '2022-05-22 07:48:13'),
(15, '31', '2.00', '2755.27', '2022-05-22 07:48:14'),
(16, '31', '2.00', '2755.27', '2022-05-22 07:48:14'),
(17, '31', '2.00', '2755.27', '2022-05-22 07:48:14'),
(18, '31', '2.00', '2755.27', '2022-05-22 07:48:15'),
(19, '31', '2.00', '2755.27', '2022-05-22 07:48:15'),
(20, '31', '2.00', '2755.27', '2022-05-22 07:48:16'),
(21, '31', '2.00', '2755.27', '2022-05-22 07:48:16'),
(22, '31', '2.00', '2755.27', '2022-05-22 07:48:16'),
(23, '31', '2.00', '2755.27', '2022-05-22 07:48:16'),
(24, '31', '2.00', '2755.27', '2022-05-22 07:48:17'),
(25, '31', '2.00', '2755.27', '2022-05-22 07:48:17'),
(26, '31', '2.00', '2755.27', '2022-05-22 07:48:17'),
(27, '31', '2.00', '2755.27', '2022-05-22 07:48:18'),
(28, '31', '2.00', '2755.27', '2022-05-22 07:48:18'),
(29, '31', '2.00', '2755.27', '2022-05-22 07:48:18'),
(30, '31', '2.00', '2755.27', '2022-05-22 07:48:18'),
(31, '31', '2.00', '2755.27', '2022-05-22 07:48:19'),
(32, '31', '2.00', '2755.27', '2022-05-22 07:48:19'),
(33, '31', '2.00', '2755.27', '2022-05-22 07:48:19'),
(34, '31', '2.00', '2755.27', '2022-05-22 07:48:20'),
(35, '31', '2.00', '2755.27', '2022-05-22 07:48:20'),
(36, '31', '2.00', '2755.27', '2022-05-22 07:48:20'),
(37, '31', '2.00', '2755.27', '2022-05-22 07:48:21'),
(38, '31', '2.00', '2755.27', '2022-05-22 07:48:21'),
(39, '31', '2.00', '2755.27', '2022-05-22 07:50:46'),
(40, '31', '2.00', '2755.27', '2022-05-22 07:50:46'),
(41, '31', '2.00', '2755.27', '2022-05-22 07:50:47'),
(42, '31', '2.00', '2755.27', '2022-05-22 07:50:47'),
(43, '31', '2.00', '2755.27', '2022-05-22 07:50:47'),
(44, '31', '2.00', '2755.27', '2022-05-22 07:50:47'),
(45, '31', '2.00', '2755.27', '2022-05-22 07:50:48'),
(46, '31', '2.00', '2755.27', '2022-05-22 07:50:48'),
(47, '31', '2.00', '2755.27', '2022-05-22 07:50:48'),
(48, '31', '2.00', '2755.27', '2022-05-22 07:50:49'),
(49, '31', '2.00', '2755.27', '2022-05-22 07:50:49'),
(50, '31', '2.00', '2755.27', '2022-05-22 07:50:49'),
(51, '31', '2.00', '2755.27', '2022-05-22 07:50:49'),
(52, '31', '2.00', '2755.27', '2022-05-22 07:50:50'),
(53, '31', '2.00', '2755.27', '2022-05-22 07:50:50'),
(54, '31', '2.00', '2755.27', '2022-05-22 07:50:50'),
(55, '31', '2.00', '2755.27', '2022-05-22 07:50:51'),
(56, '31', '2.00', '2755.27', '2022-05-22 07:50:51'),
(57, '31', '2.00', '2755.27', '2022-05-22 07:50:51'),
(58, '31', '2.00', '2755.27', '2022-05-22 07:50:51'),
(59, '31', '2.00', '2755.27', '2022-05-22 07:50:51'),
(60, '31', '2.00', '2755.27', '2022-05-22 07:50:52'),
(61, '31', '2.00', '2755.27', '2022-05-22 07:50:52'),
(62, '31', '2.00', '2755.27', '2022-05-22 07:50:52'),
(63, '31', '2.00', '2755.27', '2022-05-22 07:50:52'),
(64, '31', '2.00', '2755.27', '2022-05-22 07:50:52'),
(65, '31', '2.00', '2755.27', '2022-05-22 07:50:52'),
(66, '31', '2.00', '2755.27', '2022-05-22 07:50:52'),
(67, '31', '2.00', '2755.27', '2022-05-22 07:50:52'),
(68, '31', '2.00', '2755.27', '2022-05-22 07:50:53'),
(69, '31', '2.00', '2755.27', '2022-05-22 07:50:53'),
(70, '31', '2.00', '2755.27', '2022-05-22 07:50:53'),
(71, '31', '2.00', '2755.27', '2022-05-22 07:50:53'),
(72, '31', '2.00', '2755.27', '2022-05-22 07:50:53'),
(73, '31', '2.00', '2755.27', '2022-05-22 07:50:53'),
(74, '31', '2.00', '2755.27', '2022-05-22 07:50:54'),
(75, '31', '2.00', '2755.27', '2022-05-22 07:50:54'),
(76, '31', '2.00', '2755.27', '2022-05-22 07:50:54'),
(77, '31', '2.00', '2755.27', '2022-05-22 07:50:54'),
(78, '31', '2.00', '2755.27', '2022-05-22 07:50:54'),
(79, '31', '2.00', '2755.27', '2022-05-22 07:50:54'),
(80, '31', '2.00', '2755.27', '2022-05-22 07:50:55'),
(81, '31', '2.00', '2755.27', '2022-05-22 07:50:55'),
(82, '31', '2.00', '2755.27', '2022-05-22 07:50:55'),
(83, '31', '2.00', '2755.27', '2022-05-22 07:50:55'),
(84, '31', '2.00', '2755.27', '2022-05-22 07:50:55'),
(85, '31', '2.00', '2755.27', '2022-05-22 07:50:55'),
(86, '31', '2.00', '2755.27', '2022-05-22 08:06:20'),
(87, '31', '2.00', '2755.27', '2022-05-22 08:06:28'),
(88, '31', '2.00', '2755.27', '2022-05-22 08:06:28'),
(89, '31', '2.00', '2755.27', '2022-05-22 08:06:28'),
(90, '31', '2.00', '2755.27', '2022-05-22 08:06:29'),
(91, '31', '2.00', '2755.27', '2022-05-22 08:06:29'),
(92, '31', '2.00', '2755.27', '2022-05-22 08:06:29'),
(93, '31', '2.00', '2755.27', '2022-05-22 08:06:30'),
(94, '31', '2.00', '2755.27', '2022-05-22 08:06:30'),
(95, '31', '2.00', '2755.27', '2022-05-22 08:06:30'),
(96, '31', '2.00', '2755.27', '2022-05-22 08:06:31'),
(97, '31', '2.00', '2755.27', '2022-05-22 08:06:31'),
(98, '31', '2.00', '2755.27', '2022-05-22 08:06:31'),
(99, '31', '2.00', '2755.27', '2022-05-22 08:06:32'),
(100, '31', '2.00', '2755.27', '2022-05-22 08:19:22'),
(101, '31', '2.00', '2755.27', '2022-05-22 08:19:25'),
(102, '31', '2.00', '2755.27', '2022-05-22 08:19:25'),
(103, '31', '2.00', '2755.27', '2022-05-22 08:19:25'),
(104, '31', '2.00', '2755.27', '2022-05-22 08:19:26'),
(105, '31', '2.00', '2755.27', '2022-05-22 08:19:26'),
(106, '31', '2.00', '2755.27', '2022-05-22 08:19:26'),
(107, '31', '2.00', '2755.27', '2022-05-22 08:19:27'),
(108, '31', '2.00', '2755.27', '2022-05-22 08:19:27'),
(109, '31', '2.00', '2755.27', '2022-05-22 08:19:27'),
(110, '31', '2.00', '2755.27', '2022-05-22 08:19:28'),
(111, '31', '2.00', '2755.27', '2022-05-22 08:19:28'),
(112, '31', '2.00', '2755.27', '2022-05-22 08:19:28'),
(113, '31', '2.00', '2755.27', '2022-05-22 08:19:28'),
(114, '31', '2.00', '2755.27', '2022-05-22 08:19:29'),
(115, '31', '2.00', '2755.27', '2022-05-22 08:19:29'),
(116, '31', '2.00', '2755.27', '2022-05-22 08:19:29'),
(117, '31', '2.00', '2755.27', '2022-05-22 08:19:30'),
(118, '31', '2.00', '2755.27', '2022-05-22 08:19:30'),
(119, '31', '2.00', '2755.27', '2022-05-22 08:19:30'),
(120, '31', '2.00', '2755.27', '2022-05-22 08:19:31'),
(121, '31', '2.00', '2755.27', '2022-05-22 08:19:31'),
(122, '31', '2.00', '2755.27', '2022-05-22 08:19:31'),
(123, '31', '2.00', '2755.27', '2022-05-22 08:19:32'),
(124, '31', '2.00', '2755.27', '2022-05-22 08:19:32'),
(125, '31', '2.00', '2755.27', '2022-05-22 08:19:32'),
(126, '31', '2.00', '2755.27', '2022-05-22 08:19:32'),
(127, '31', '2.00', '2755.27', '2022-05-22 08:19:32'),
(128, '31', '2.00', '2755.27', '2022-05-22 08:19:32'),
(129, '31', '2.00', '2755.27', '2022-05-22 08:19:33'),
(130, '31', '2.00', '2755.27', '2022-05-22 08:19:33'),
(131, '31', '2.00', '2755.27', '2022-05-22 08:19:33'),
(132, '31', '2.00', '2755.27', '2022-05-22 08:19:33'),
(133, '31', '2.00', '2755.27', '2022-05-22 08:19:35'),
(134, '31', '2.00', '2755.27', '2022-05-22 08:19:35'),
(135, '31', '2.00', '2755.27', '2022-05-22 08:19:35'),
(136, '31', '2.00', '2755.27', '2022-05-22 08:19:35'),
(137, '31', '2.00', '2755.27', '2022-05-22 08:19:35'),
(138, '31', '2.00', '2755.27', '2022-05-22 08:19:35'),
(139, '31', '2.00', '2755.27', '2022-05-22 08:19:35'),
(140, '31', '2.00', '2755.27', '2022-05-22 08:19:35'),
(141, '31', '2.00', '2755.27', '2022-05-22 08:19:36'),
(142, '31', '2.00', '2755.27', '2022-05-22 08:19:36'),
(143, '31', '2.00', '2755.27', '2022-05-22 08:19:36'),
(144, '31', '2.00', '2755.27', '2022-05-22 08:19:36'),
(145, '31', '2.00', '2755.27', '2022-05-22 08:19:36'),
(146, '31', '2.00', '2755.27', '2022-05-22 08:19:36'),
(147, '31', '2.00', '2755.27', '2022-05-22 08:19:36'),
(148, '31', '2.00', '2755.27', '2022-05-22 08:19:36'),
(149, '31', '2.00', '2755.27', '2022-05-22 08:19:36'),
(150, '31', '2.00', '2755.27', '2022-05-22 08:19:37'),
(151, '24', '2.00', '2755.27', '2022-05-22 08:19:37'),
(152, '22', '2.00', '2755.27', '2022-05-22 08:19:37'),
(153, '21', '2.00', '2755.27', '2022-05-22 08:19:37'),
(154, '18', '2.00', '2755.27', '2022-05-22 08:19:37'),
(155, '19', '2.00', '2755.27', '2022-05-22 08:19:37'),
(156, '20', '2.00', '2755.27', '2022-05-22 08:19:37'),
(157, '23', '2.00', '2755.27', '2022-05-22 08:19:37'),
(158, '28', '2.00', '2755.27', '2022-05-22 08:19:37'),
(159, '25', '2.00', '2755.27', '2022-05-22 08:19:38'),
(160, '32', '2.00', '2755.27', '2022-05-22 08:19:38'),
(161, '31', '2.00', '300', '2022-05-22 08:19:38');

-- --------------------------------------------------------

--
-- Struktur dari tabel `statuscontrol`
--

CREATE TABLE `statuscontrol` (
  `idStatus` int(11) NOT NULL,
  `namaControl` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `statuscontrol`
--

INSERT INTO `statuscontrol` (`idStatus`, `namaControl`) VALUES
(1, 'Time Aktif'),
(2, 'Manual Aktif');

-- --------------------------------------------------------

--
-- Struktur dari tabel `statusfeeder`
--

CREATE TABLE `statusfeeder` (
  `idstatus` int(11) NOT NULL,
  `namafeeder` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `statusfeeder`
--

INSERT INTO `statusfeeder` (`idstatus`, `namafeeder`) VALUES
(1, 'Button Manual Aktif'),
(0, 'Button Manual Tidak ');

-- --------------------------------------------------------

--
-- Struktur dari tabel `users`
--

CREATE TABLE `users` (
  `id_users` int(11) NOT NULL,
  `nama` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `avatar` varchar(255) NOT NULL,
  `date_updated` timestamp NULL DEFAULT NULL,
  `date_created` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `users`
--

INSERT INTO `users` (`id_users`, `nama`, `email`, `password`, `avatar`, `date_updated`, `date_created`) VALUES
(1, 'Rizqi Wijaya', 'rizqiEmail@gmail.com', '$2a$04$NM0FNu1yM.kemDAJKSwkXeFmIVSF1sgw/ZdpIRmjn0F821BEIPyc6', '', NULL, NULL),
(2, 'Rizwijaya', 'Rizqi2@gmail.com', '$2a$04$mvffeMmJXhpiSJfhAkOdZ.G8F9/xwmPLwA/oCRQkAUMVEv/8ko0fW', 'Images/avatar.png', '0000-00-00 00:00:00', '0000-00-00 00:00:00');

--
-- Indexes for dumped tables
--

--
-- Indeks untuk tabel `monitoring`
--
ALTER TABLE `monitoring`
  ADD PRIMARY KEY (`id`);

--
-- Indeks untuk tabel `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id_users`);

--
-- AUTO_INCREMENT untuk tabel yang dibuang
--

--
-- AUTO_INCREMENT untuk tabel `monitoring`
--
ALTER TABLE `monitoring`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=162;

--
-- AUTO_INCREMENT untuk tabel `users`
--
ALTER TABLE `users`
  MODIFY `id_users` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
