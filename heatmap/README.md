# Heatmap for Key Usage Tracking

## Generate the Database
``` sql
CREATE TABLE `keycount` (
  `id` int NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `time` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `user` varchar(64) NOT NULL COMMENT '256-bit User Hash',
  `count` varchar(500) NOT NULL COMMENT 'Python-formatted List of Key Counts'
) DEFAULT CHARSET=utf8;
```

## Install Python packages on the server
``` shell
python3 -m pip install mysql-connector-python
python3 -m pip install matplotlib
python3 -m pip install scipy
```
