# Heatmap for Key Usage Tracking

## Generate the Database

Table to register the users with their physical keymaps:

``` sql
CREATE TABLE `keymap` (
  `user` varchar(64) NOT NULL PRIMARY KEY COMMENT '256-bit User Hash',
  `map` varchar(500) NOT NULL COMMENT 'Array of Physical Key Widths',
  `rows` int NOT NULL COMMENT 'Number of Physical Rows',
  `cols` int NOT NULL COMMENT 'Number of Physical Columns'
) DEFAULT CHARSET=utf8;
```

Table to store the keycounts of the users:

``` sql
CREATE TABLE `keycount` (
  `id` int NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `time` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `user` varchar(64) NOT NULL,
  `count` varchar(500) NOT NULL COMMENT 'Python-formatted List of Key Counts',
  FOREIGN KEY (`user`) REFERENCES `keymap`(`user`)
) DEFAULT CHARSET=utf8;
```

## Install Python packages on the server

``` shell
python3 -m pip install mysql-connector-python
python3 -m pip install matplotlib
python3 -m pip install scipy
```

## Deploy all or single files to the server

Enable SSH key access on the server.
Source the credentials script to set variables for `USERNAME`, `SERVER` and `DIRECTORY`.

``` shell
source deploy_credentials.sh
```

Deploy all files except directories and files specified in the `exclude_list`.
Optionally, pass the single `<file>` to be uploaded.

``` shell
./deploy.sh [-f <file>]
```
