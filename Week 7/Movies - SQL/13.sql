/* list the names of all people who starred in a movie in which Kevin Bacon also starred */


SELECT name FROM stars
JOIN people ON stars.person_id = people.id
WHERE movie_id IN (
SELECT movie_id FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
WHERE name = "Kevin Bacon" AND birth = 1958
) AND name != "Kevin Bacon";