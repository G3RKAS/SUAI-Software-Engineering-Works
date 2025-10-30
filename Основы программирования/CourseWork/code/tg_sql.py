import mysql.connector as sql
from mysql.connector import errorcode

server = None

config = {
  'user': '',
  'password': '',
  'host': '',
  'database': '',
  'raise_on_warnings': True
}


try:
    server = sql.connect(**config)
except sql.Error as err:
    print("БАЗА НЕ ПОДКЛЮЧЕНА")
    if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
        print("Данные неверны!")
    elif err.errno == errorcode.ER_BAD_DB_ERROR:
        print("БД не существует!")
    else:
        print(err)

def check_server():
    if not server:
        return None
    if not server.is_connected():
        return None
    return True

def check_and_retry_connection():
    if not server.is_connected():
        server.reconnect(attempts=5, delay=2)

def is_user_train_in_bd_by_name(tg_id, name):
    data = get_all_user_train(tg_id)
    for items in data:
        if items['train_name'] == name:
            return True
    return False

def is_user_in_users(tg_id):
    data = get_data_from_users(tg_id)
    if not data:
        return False
    else:
        return True

def is_user_profile_contain_trains(tg_id):
    data = get_data_from_users(tg_id)
    if data["trains"] is None:
        return False
    return True

def is_user_profile_full(tg_id):
    data = get_data_from_users(tg_id)
    if data["height"] is None or data["weight"] is None or data["age"] is None:
        return False
    return True

def get_data_from_users(tg_id):
    check_and_retry_connection()
    server.commit()
    curs = server.cursor(dictionary=True)
    query = "SELECT * FROM users WHERE tg_id = %s"
    curs.execute(query, (str(tg_id),))
    data = curs.fetchone()
    curs.close()

    return data


def set_user_age(tg_id, age):
    check_and_retry_connection()
    curs = server.cursor(buffered=True)
    if not is_user_in_users(tg_id):
        query = "INSERT INTO users (tg_id, age) VALUES (%s, %s)"
        curs.execute(query, (str(tg_id), int(age)))
    else:
        query = "UPDATE users SET age = %s WHERE tg_id = %s"
        curs.execute(query, (int(age), str(tg_id)))
    server.commit()
    curs.close()

def set_user_weight(tg_id, weight):
    check_and_retry_connection()
    curs = server.cursor(buffered=True)
    if not is_user_in_users(tg_id):
        query = "INSERT INTO users (tg_id, weight) VALUES (%s, %s)"
        curs.execute(query, (str(tg_id), int(weight)))
    else:
        query = "UPDATE users SET weight = %s WHERE tg_id = %s"
        curs.execute(query, (int(weight), str(tg_id)))
    server.commit()
    curs.close()

def set_user_height(tg_id, height):
    check_and_retry_connection()
    curs = server.cursor(buffered=True)
    if not is_user_in_users(tg_id):
        query = "INSERT INTO users (tg_id, height) VALUES (%s, %s)"
        curs.execute(query, (str(tg_id), int(height)))
    else:
        query = "UPDATE users SET height = %s WHERE tg_id = %s"
        curs.execute(query, (int(height), str(tg_id)))
    server.commit()
    curs.close()


def set_user_info(tg_id, add_info):
    check_and_retry_connection()
    curs = server.cursor(buffered=True)
    if not is_user_in_users(tg_id):
        query = "INSERT INTO users (tg_id, add_info) VALUES (%s, %s)"
        curs.execute(query, (str(tg_id), add_info))
    else:
        query = "UPDATE users SET add_info = %s WHERE tg_id = %s"
        curs.execute(query, (add_info, str(tg_id)))
    server.commit()
    curs.close()

def set_user_trains(tg_id, trains):
    check_and_retry_connection()
    curs = server.cursor(buffered=True)
    if not is_user_in_users(tg_id):
        query = "INSERT INTO users (tg_id, trains) VALUES (%s, %s)"
        curs.execute(query, (str(tg_id), trains))
    else:
        query = "UPDATE users SET trains = %s WHERE tg_id = %s"
        curs.execute(query, (trains, str(tg_id)))
    server.commit()
    curs.close()

def get_all_users_trains_by_page():
    check_and_retry_connection()
    server.commit()
    curs = server.cursor(dictionary=True)
    query = "SELECT * FROM trains_users"
    curs.execute(query)
    data = curs.fetchall()
    curs.close()

    return data

def get_all_user_train(tg_id):
    check_and_retry_connection()
    server.commit()
    curs = server.cursor(dictionary=True)

    query = "SELECT * FROM `trains_users` WHERE tg_id = %s"
    curs.execute(query, (str(tg_id),))
    data = curs.fetchall()

    curs.close()

    return data

def upload_user_train(tg_id, name, trains, desc):
    check_and_retry_connection()
    curs = server.cursor(buffered=True)

    query = "INSERT INTO  trains_users(`tg_id`, `train_name`, `trains`, `descp`) VALUES (%s, %s, %s, %s)"
    curs.execute(query, (str(tg_id), name, trains, desc))

    server.commit()
    curs.close()

def delete_user_train_by_name(tg_id, name):
    check_and_retry_connection()
    curs = server.cursor(buffered=True)

    query = "DELETE FROM `trains_users` WHERE `tg_id` = %s AND `train_name` = %s LIMIT 1"

    curs.execute(query, (str(tg_id), name))

    server.commit()
    curs.close()

def get_user_train_by_name(tg_id, name):
    check_and_retry_connection()
    server.commit()
    curs = server.cursor(dictionary=True)

    query = "SELECT * FROM `trains_users` WHERE `tg_id` = %s AND `train_name` = %s"
    curs.execute(query, (str(tg_id), name))
    data = curs.fetchall()

    curs.close()

    return data

def get_all_trains():
    check_and_retry_connection()
    server.commit()
    curs = server.cursor(dictionary=True)

    query = "SELECT * FROM `trains`"
    curs.execute(query)
    data = curs.fetchall()

    curs.close()

    return data