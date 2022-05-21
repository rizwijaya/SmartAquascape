-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: May 21, 2022 at 04:20 AM
-- Server version: 10.4.20-MariaDB
-- PHP Version: 8.0.9

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `smart_aquascape`
--

-- --------------------------------------------------------

--
-- Table structure for table `deliver_time`
--

CREATE TABLE `deliver_time` (
  `id` int(11) NOT NULL,
  `time_deliver` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `devices`
--

-- --------------------------------------------------------

--
-- Table structure for table `feeder`
--

CREATE TABLE `feeder` (
  `id` int(11) DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  `status_feeder` int(11) DEFAULT NULL,
  `WaktuReq` datetime DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `monitoring`
--

CREATE TABLE `monitoring` (
  `id` int(11) NOT NULL,
  `temperature` varchar(255) NOT NULL,
  `water_level` varchar(255) NOT NULL,
  `turbidity` varchar(255) NOT NULL,
  `request_time` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `sensor_time`
--

CREATE TABLE `sensor_time` (
  `id` int(11) NOT NULL,
  `status_time` int(11) NOT NULL,
  `on_hours` datetime NOT NULL,
  `on_minutes` datetime NOT NULL,
  `off_hours` datetime NOT NULL,
  `off_minutes` datetime NOT NULL,
  `time_req` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `temperature`
--

CREATE TABLE `temperature` (
  `temperature_id` varchar(255) NOT NULL,
  `temperature` float NOT NULL,
  `time` datetime DEFAULT NULL,
  `data` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `turbidity`
--

CREATE TABLE `turbidity` (
  `turbidity_id` varchar(255) NOT NULL,
  `turbidity` float NOT NULL,
  `time` datetime NOT NULL,
  `data` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `id_user` int(11) NOT NULL,
  `id_kawasan` int(11) NOT NULL,
  `nama` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `avatar` varchar(255) NOT NULL,
  `id_role` int(11) NOT NULL,
  `date_updated` timestamp NULL DEFAULT NULL,
  `date_created` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`id_user`, `id_kawasan`, `nama`, `email`, `password`, `avatar`, `id_role`, `date_updated`, `date_created`) VALUES
(1, 1, 'herwinda', 'herwinda@email.com', 'herwinda24', '', 1, '2022-05-20 13:22:53', '2022-05-20 13:22:53');

-- --------------------------------------------------------

--
-- Table structure for table `water_level`
--

CREATE TABLE `water_level` (
  `waterlevel_id` varchar(255) NOT NULL,
  `water_level` float NOT NULL,
  `time` datetime NOT NULL,
  `data` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `devices`
--
ALTER TABLE `devices`
  ADD PRIMARY KEY (`no_device`);

--
-- Indexes for table `monitoring`
--
ALTER TABLE `monitoring`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sensor_time`
--
ALTER TABLE `sensor_time`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `temperature`
--
ALTER TABLE `temperature`
  ADD PRIMARY KEY (`temperature_id`);

--
-- Indexes for table `turbidity`
--
ALTER TABLE `turbidity`
  ADD PRIMARY KEY (`turbidity_id`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`id_user`);

--
-- Indexes for table `water_level`
--
ALTER TABLE `water_level`
  ADD PRIMARY KEY (`waterlevel_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `devices`
--
ALTER TABLE `devices`
  MODIFY `no_device` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `monitoring`
--
ALTER TABLE `monitoring`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `sensor_time`
--
ALTER TABLE `sensor_time`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `id_user` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
