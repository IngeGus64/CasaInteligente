def get_data(interval):

	conn = sqlite3.connect(dbname)
	curs = conn.cursor()

	if interval == None:
		curs.execute("SELECT * FROM temps")
	else:
		curs.execute("SELECT * FROM temps WHERE timestamp > datetime('now','-%s hours')" % interval)

	rows = curs.fetchall()

	conn.close()

	return rows
