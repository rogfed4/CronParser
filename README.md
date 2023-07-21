#  Cron Expression Parser 

This is a command line application which parses a cron string and expands each field to show the times at which it will run.
Only five time fields (minute, hour, day of month, month, and day of week) plus a command are considered in this application.

The cron expression consists of five fields:

Minute: The minute field represents the minutes within an hour (0 to 59).
Hour: The hour field represents the hour of the day (0 to 23).
Day of the Month: The day of the month field represents the day of the month (1 to 31).
Month: The month field represents the month of the year (1 to 12).
Day of the Week: The day of the week field represents the day of the week (1 to 7, where both 1 and 7 represent Monday andSunday).


*1. Minute Field:*

The minute field in a cron expression allows you to specify the minute(s) at which the task should be executed. Valid values range from 0 to 59, and you can use single numbers, comma-separated lists, hyphenated ranges, and the * wildcard.

Examples:
- `0` - Execute at minute 0.
- `*/15` - Execute every 15 minutes.
- `5,10,20` - Execute at minutes 5, 10, and 20.
- `15-30` - Execute from minutes 15 to 30.

*2. Hour Field:*

The hour field in a cron expression defines the hour(s) when the task should run. Valid values range from 0 to 23, and you can use the same syntax as in the minute field.

Examples:
- `0` - Execute at hour 0 (midnight).
- `*/2` - Execute every 2 hours.
- `9,18` - Execute at 9 AM and 6 PM.
- `9-17` - Execute from 9 AM to 5 PM.

*3. Day of the Month Field:*

The day of the month field specifies the day(s) of the month when the task should run. Valid values range from 1 to 31, and you can use the same syntax as in the minute and hour fields.

Examples:
- `1` - Execute on the 1st day of the month.
- `*/5` - Execute every 5 days of the month.
- `10,20,31` - Execute on the 10th, 20th, and 31st day of the month.
- `5-15` - Execute from the 5th to the 15th day of the month.

*4. Month Field:*

The month field allows you to specify the month(s) when the task should run. Valid values range from 1 to 12 (January to December), and you can use the same syntax as in the previous fields.

Examples:
- `1` - Execute in January.
- `*/3` - Execute every 3 months.
- `4,7,10` - Execute in April, July, and October.
- `2-6` - Execute from February to June.

*5. Day of the Week Field:*

The day of the week field defines the day(s) of the week when the task should run. Valid values range from 1 to 7, where 1 represents Monday. 

Examples:
- `1` - Execute on Mondays.
- `*/2` - Execute every 2 days of the week.
- `1,3,5` - Execute on Mondays, Wednesdays, and Fridays.
- `1-5` - Execute from Monday to Friday.

Special Characters:*

In addition to the numerical values, you can use some special characters in a cron expression:

- `*` (Asterisk) - Matches all valid values for the respective field.
- `/` (Slash) - Specifies the step value between two elements in the range.
- `,` (Comma) - Lists multiple values.
- `-` (Hyphen) - Specifies a range of values.

*Examples:*

1. `*/15 * * * *` - Execute every 15 minutes.
2. `0 2 * * *` - Execute at 2 AM daily.
3. `30 12 1-15 * *` - Execute at 12:30 PM from the 1st to the 15th day of the month.
4. `0 0 1 */3 *` - Execute at midnight on the 1st day of every 3rd month.
5. `0 8,18 * * 1-5` - Execute at 8 AM and 6 PM from Monday to Friday.

## Setup
To run this project: 
```
make parse
```

##  Sample Input
```
./parse "*/15 0 1,15 * 1-5 /usr/bin/find"
```

## Sample Output
```
minute        0 15 30 45
hour          0
day of month  1 15
month         1 2 3 4 5 6 7 8 9 10 11 12
day of week   1 2 3 4 5
command       /usr/bin/find
```

## Tests
To run tests: 
```
make testrun
```

## To run a sample example:
```
make example
```

## To remove all compiled files:
```
make clean
```