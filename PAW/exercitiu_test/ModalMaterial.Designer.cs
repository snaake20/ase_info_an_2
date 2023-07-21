namespace PregatireTest1
{
	partial class ModalMaterial
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.LblId = new System.Windows.Forms.Label();
			this.LblDenumire = new System.Windows.Forms.Label();
			this.LblPret = new System.Windows.Forms.Label();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.textBox2 = new System.Windows.Forms.TextBox();
			this.textBox3 = new System.Windows.Forms.TextBox();
			this.BtnActiune = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// LblId
			// 
			this.LblId.AutoSize = true;
			this.LblId.Location = new System.Drawing.Point(12, 9);
			this.LblId.Name = "LblId";
			this.LblId.Size = new System.Drawing.Size(19, 13);
			this.LblId.TabIndex = 0;
			this.LblId.Text = "Id:";
			// 
			// LblDenumire
			// 
			this.LblDenumire.AutoSize = true;
			this.LblDenumire.Location = new System.Drawing.Point(12, 33);
			this.LblDenumire.Name = "LblDenumire";
			this.LblDenumire.Size = new System.Drawing.Size(55, 13);
			this.LblDenumire.TabIndex = 1;
			this.LblDenumire.Text = "Denumire:";
			// 
			// LblPret
			// 
			this.LblPret.AutoSize = true;
			this.LblPret.Location = new System.Drawing.Point(12, 55);
			this.LblPret.Name = "LblPret";
			this.LblPret.Size = new System.Drawing.Size(29, 13);
			this.LblPret.TabIndex = 2;
			this.LblPret.Text = "Pret:";
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(37, 6);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(100, 20);
			this.textBox1.TabIndex = 3;
			// 
			// textBox2
			// 
			this.textBox2.Location = new System.Drawing.Point(73, 30);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new System.Drawing.Size(100, 20);
			this.textBox2.TabIndex = 4;
			// 
			// textBox3
			// 
			this.textBox3.Location = new System.Drawing.Point(47, 52);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new System.Drawing.Size(100, 20);
			this.textBox3.TabIndex = 5;
			// 
			// BtnActiune
			// 
			this.BtnActiune.Location = new System.Drawing.Point(37, 87);
			this.BtnActiune.Name = "BtnActiune";
			this.BtnActiune.Size = new System.Drawing.Size(75, 23);
			this.BtnActiune.TabIndex = 6;
			this.BtnActiune.UseVisualStyleBackColor = true;
			this.BtnActiune.Click += new System.EventHandler(this.BtnActiune_Click);
			// 
			// ModalMaterial
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.BtnActiune);
			this.Controls.Add(this.textBox3);
			this.Controls.Add(this.textBox2);
			this.Controls.Add(this.textBox1);
			this.Controls.Add(this.LblPret);
			this.Controls.Add(this.LblDenumire);
			this.Controls.Add(this.LblId);
			this.Name = "ModalMaterial";
			this.Text = "ModalMaterial";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label LblId;
		private System.Windows.Forms.Label LblDenumire;
		private System.Windows.Forms.Label LblPret;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.TextBox textBox2;
		private System.Windows.Forms.TextBox textBox3;
		private System.Windows.Forms.Button BtnActiune;
	}
}