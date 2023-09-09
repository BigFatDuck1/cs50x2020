/*--List the titles and release years of all Harry Potter movies, in chronological order--*/

SELECT year, title FROM movies WHERE title LIKE "Harry Potter%" ORDER BY year;
/*SELECT title, year FROM movies WHERE title LIKE "Harry Potter%";*/