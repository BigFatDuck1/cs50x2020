/* list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated */

SELECT title FROM movies
JOIN ratings ON movies.id = ratings.movie_id
JOIN stars on stars.movie_id = movies.id
JOIN people on people.id = stars.person_id
WHERE name = 'Chadwick Boseman'
ORDER BY rating DESC
LIMIT 5;