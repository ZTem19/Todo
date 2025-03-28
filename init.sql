
CREATE TABLE todo(
	id INTEGER PRIMARY KEY,
	title VARCHAR(10) NOT NULL,
	description VARCHAR(50)
);

INSERT INTO todo(id, title) VALUES
(1, 'finish this project'),
(2, 'finish school');

