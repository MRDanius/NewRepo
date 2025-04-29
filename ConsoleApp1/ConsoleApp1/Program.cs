using System.Threading;
using System;

namespace threads_start
{
    class Program
    {
        class Seat
        {
            public int id = 0;
            public bool booked = false;
            public int owner = 0;
        }

        class BookingSystem
        {
            public int num = 0;
            public Seat seat;
            public bool bookingCompleted;

            public BookingSystem(int n, Seat s)
            {
                this.num = n;
                this.seat = s;
            }

            public void Book()
            {
                if (!seat.booked)
                {
                    Console.WriteLine("Seat if free! Try book by system " + this.num);
                    this.bookingCompleted = true;
                    seat.owner = this.num;
                    Console.WriteLine("Booked by system " + this.num);
                    seat.booked = true;
                }
            }
        }

        void run()
        {
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine(i);
            }
        }


        static void Main(string[] args)
        {
            int n = 1000;
            int race_count = 0;


            for (int i = 0; i < n; i++)
            {
                Seat seat = new Seat();

                BookingSystem firstSys = new BookingSystem(1, seat);
                BookingSystem secondSys = new BookingSystem(2, seat);






                Program p = new Program();

                Thread first = new Thread(firstSys.Book);
                Thread second = new Thread(secondSys.Book);

                first.Start();
                second.Start();

                first.Join();
                second.Join();

                if (firstSys.bookingCompleted && secondSys.bookingCompleted)
                {
                    race_count++;
                }

                Thread.Sleep(10);

            }

            Console.WriteLine(race_count);
        }
    }
}