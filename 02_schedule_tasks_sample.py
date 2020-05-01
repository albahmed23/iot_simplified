import schedule
import datetime
import time


# Dict for a time table of the daily schedule (this needs to be changed to something more effecient)
YEAR = 2020
schedule_dict = {
    datetime.date(YEAR, 4,30) : ["16:13","05:29","13:20"],
    datetime.date(YEAR, 5,1) : ["05:00","05:28","13:20"],
    datetime.date(YEAR, 5,2) : ["04:50","05:27","13:19"]
    }

# Some functions
def do_something():
  print("Doing something")
  
def fly_early():
  print("I am flying earlier")
  
def goodnight():
  print("Goodnight")
  

# Function to make the schedule
def make_schedule(schedule_dict,date):
  todays_schedule = schedule_dict[date]
  
  #Run the schedule
  schedule.every().day.at(todays_schedule[0]).do(do_something)
  schedule.every().day.at(todays_schedule[1]).do(fly_early)
  schedule.every().day.at(todays_schedule[2]).do(goodnight)
  

if __name__ == "__main__":

    while True:

        todays_date_started = datetime.date.today()

        make_schedule(schedule_dict,todays_date_started)
    
        while True:
            todays_date = datetime.date.today()

            #while it's within today's date
            if(todays_date == todays_date_started):
                schedule.run_pending()
                time.sleep(1)
            elif(todays_date != todays_date_started):
                schedule.clear() # Clear schedule before leaving
                break
