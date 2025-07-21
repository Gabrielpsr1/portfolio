-- Keep a log of any SQL queries you execute as you solve the mystery.

-- I want to see the description of the crime
SELECT description FROM crime_scene_reports WHERE year = 2024 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted
--today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

SELECT name,transcript FROM interviews WHERE year = 2024 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%' ;
-- | Ruth    | Sometime XXXXXXXXXXXXX within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. XXXXXXXXXXX
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
--  I was walking by the XXXXXXXXXXX ATM on Leggett Street and saw the thief there withdrawing some money. XXXXXXXX                                                                                               |
-- | Raymond | As the thief was leaving the bakery, XXXXXXX they called someone who talked to them for less than a minute. XXXXXXXX
-- In the call, I heard the thief say that they were planning to take the XXXXXXXX earliest flight out
--  of Fiftyville tomorrow XXXXXXXXXXXX. The thief then asked the person on the other end of the phone to XXXXXXXpurchase the flight ticket.XXXXXXXXX |

-- Lets see who went to the bakery
SELECT name,phone_number,passport_number,minute,activity FROM people join bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate  WHERE
year = 2024 AND month = 7 AND day = 28 AND hour = 10;
-- +---------+----------------+-----------------+--------+----------+
-- |  name   |  phone_number  | passport_number | minute | activity |
-- +---------+----------------+-----------------+--------+----------+
-- | Brandon | (771) 555-6667 | 7874488539      | 8      | entrance |
-- | Sophia  | (027) 555-1068 | 3642612721      | 14     | entrance |

-- these are the suspect people
-- | Vanessa | (725) 555-4692 | 2963008352      | 16     | exit     |
-- | Bruce   | (367) 555-5533 | 5773159633      | 18     | exit     |
-- | Barry   | (301) 555-4174 | 7526138472      | 18     | exit     |
-- | Luca    | (389) 555-5198 | 8496433585      | 19     | exit     |
-- | Sofia   | (130) 555-0289 | 1695452385      | 20     | exit     |
-- | Iman    | (829) 555-5269 | 7049073643      | 21     | exit     |
-- | Diana   | (770) 555-1861 | 3592750733      | 23     | exit     |
-- | Kelsey  | (499) 555-9472 | 8294398571      | 23     | exit     |


-- | Taylor  | (286) 555-6063 | 1988161715      | 35     | exit     |
-- | Denise  | (994) 555-3373 | 4001449165      | 42     | entrance |
-- | Thomas  | (286) 555-0131 | 6034823042      | 44     | entrance |
-- | Jeremy  | (194) 555-5027 | 1207566299      | 55     | entrance |
-- +---------+----------------+-----------------+--------+----------+


-- by this line, i'll know every one that went to the atm on the street mentioned by the witness and who also went to the bakery
SELECT name,phone_number,passport_number FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street'))
AND license_plate IN(SELECT license_plate FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28
AND hour = 10 AND minute < 25 AND activity = 'exit');

-- +-------+----------------+-----------------+
-- | name  |  phone_number  | passport_number |
-- +-------+----------------+-----------------+
-- | Iman  | (829) 555-5269 | 7049073643      |
-- | Luca  | (389) 555-5198 | 8496433585      |
-- | Diana | (770) 555-1861 | 3592750733      |
-- | Bruce | (367) 555-5533 | 5773159633      |
-- +-------+----------------+-----------------+
-- These are the sus people

--know we'll know which suspects called someone after leaving the bakery
SELECT name,phone_number,passport_number FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street'))
AND license_plate IN(SELECT license_plate FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28
AND hour = 10 AND minute < 25 AND activity = 'exit')
AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60);
-- +-------+----------------+-----------------+
-- | name  |  phone_number  | passport_number |
-- +-------+----------------+-----------------+
-- | Diana | (770) 555-1861 | 3592750733      |
-- | Bruce | (367) 555-5533 | 5773159633      |
-- +-------+----------------+-----------------+
-- last two suspects


-- to figure out where the first flight out fiftyville is going to
SELECT city FROM airports WHERE id = (SELECT origin_airport_id FROM flights WHERE year = 2024 AND month = 7 AND day = 29 ORDER BY hour,minute AND origin_airport_id in
(SELECT id FROM airports) LIMIT 1);
--the thief went to nyc


-- to see which one of the two suspects where in the first flight out of ny
SELECT name,phone_number,passport_number FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street'))
AND license_plate IN(SELECT license_plate FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28
AND hour = 10 AND minute < 25 AND activity = 'exit')
AND phone_number IN
(SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60)
AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id =
(SELECT id FROM flights WHERE year = 2024 AND month = 7 AND day = 29 ORDER BY hour,minute AND origin_airport_id in
(SELECT id FROM airports WHERE city = 'New York') LIMIT 1));
-- +-------+----------------+-----------------+
-- | name  |  phone_number  | passport_number |
-- +-------+----------------+-----------------+
-- | Bruce | (367) 555-5533 | 5773159633      |
-- +-------+----------------+-----------------+
-- Bruce is the thief

-- Let's see who is the ACCOMPLICE
SELECT name FROM people WHERE phone_number =
(SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533' AND year = 2024 AND month = 7 AND day = 28 AND duration < 60);
-- +-------+
-- | name  |
-- +-------+
-- | Robin |
-- +-------+
-- it's robin
